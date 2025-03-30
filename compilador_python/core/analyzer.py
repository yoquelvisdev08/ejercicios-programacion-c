"""
Módulo para analizar el código fuente C++.
"""

import re
import os
import traceback
from nltk.tokenize import word_tokenize
from nltk.tag import pos_tag

class CppAnalyzer:
    """Clase para analizar el código fuente C++ y determinar sus características."""
    
    def __init__(self):
        """Inicializar el analizador."""
        # Patrones para diferentes tipos de ejercicios
        self.patterns = {
            "vector": [
                r'vector\s*<',
                r'array\s*<',
                r'int\s+\w+\s*\[\s*\d*\s*\]',
                r'float\s+\w+\s*\[\s*\d*\s*\]',
                r'double\s+\w+\s*\[\s*\d*\s*\]',
            ],
            "matriz": [
                r'int\s+\w+\s*\[\s*\d*\s*\]\s*\[\s*\d*\s*\]',
                r'float\s+\w+\s*\[\s*\d*\s*\]\s*\[\s*\d*\s*\]',
                r'double\s+\w+\s*\[\s*\d*\s*\]\s*\[\s*\d*\s*\]',
                r'vector\s*<\s*vector\s*<',
                r'matriz|matrix',
                r'filas|columnas|rows|columns'
            ],
            "cadena": [
                r'string\s+\w+',
                r'char\s+\w+\s*\[\s*\d*\s*\]',
                r'substr|concatena|reverse|length',
                r'strlen|strcpy|strcat',
                r'getline'
            ],
            "estructura": [
                r'struct\s+\w+',
                r'class\s+\w+',
                r'typedef\s+struct',
                r'private:|public:|protected:',
                r'objeto|instance'
            ]
        }
        
        # Palabras clave específicas por tipo
        self.keywords = {
            "vector": [
                "array", "vector", "arreglo", "lista", "colección", 
                "elemento", "posición", "índice", "ordenar", "buscar"
            ],
            "matriz": [
                "matriz", "matrix", "bidimensional", "fila", "columna", 
                "row", "column", "tabla", "cuadrícula", "grid"
            ],
            "cadena": [
                "string", "cadena", "texto", "caracter", "palabra", 
                "subcadena", "concatenar", "invertir", "mayúscula", "minúscula"
            ],
            "estructura": [
                "estructura", "struct", "clase", "class", "objeto", 
                "atributo", "método", "member", "instancia", "herencia"
            ]
        }
    
    def analyze_file(self, filepath):
        """Analiza un archivo C++ para determinar sus características."""
        try:
            # Leer el contenido del archivo
            with open(filepath, 'r', encoding='utf-8') as file:
                content = file.read()
            
            # Analizar el código
            return self.analyze_code(content, filepath)
            
        except Exception as e:
            print(f"Error al analizar archivo: {e}")
            traceback.print_exc()
            return {"error": str(e), "type": "default"}
    
    def analyze_code(self, code, filename=None):
        """Analiza el código C++ para determinar sus características y tipo."""
        try:
            # Inicializar resultados
            analysis = {
                "type": "default",            # Tipo de ejercicio (vector, matriz, cadena, estructura)
                "complexity": 0,              # Complejidad estimada (0-100)
                "requires_input": False,      # Si requiere entrada del usuario
                "input_types": [],            # Tipos de entrada requeridos
                "has_classes": False,         # Si usa clases
                "has_structs": False,         # Si usa estructuras
                "detected_patterns": {},      # Patrones detectados por tipo
                "lines_of_code": 0,           # Líneas de código (sin comentarios ni vacías)
                "includes": [],               # Bibliotecas incluidas
                "main_function": False,       # Si tiene función main
                "functions": [],              # Funciones definidas
            }
            
            # Contar líneas de código no vacías y que no sean comentarios
            lines = code.split('\n')
            code_lines = []
            for line in lines:
                line = line.strip()
                if line and not line.startswith('//') and not line.startswith('/*'):
                    code_lines.append(line)
            analysis["lines_of_code"] = len(code_lines)
            
            # Detectar includes
            analysis["includes"] = re.findall(r'#include\s*[<"]([^>"]+)[>"]', code)
            
            # Detectar función main
            analysis["main_function"] = bool(re.search(r'int\s+main\s*\([^)]*\)', code))
            
            # Detectar clases y estructuras
            analysis["has_classes"] = bool(re.findall(r'class\s+\w+', code))
            analysis["has_structs"] = bool(re.findall(r'struct\s+\w+', code))
            
            # Detectar funciones
            analysis["functions"] = re.findall(r'(?:void|int|float|double|char|bool|string)\s+(\w+)\s*\([^)]*\)', code)
            
            # Detectar si requiere entrada
            if 'cin' in code or 'getline' in code or 'scanf' in code:
                analysis["requires_input"] = True
                
                # Detectar tipos de variables usadas con cin
                cin_vars = re.findall(r'cin\s*>>\s*(\w+)', code)
                for var in cin_vars:
                    # Buscar la declaración de la variable
                    var_decl = re.findall(rf'(?:int|float|double|char|string)\s+{var}\s*;', code)
                    if var_decl:
                        var_type = var_decl[0].split()[0]
                        if var_type not in analysis["input_types"]:
                            analysis["input_types"].append(var_type)
            
            # Detectar patrones por tipo de ejercicio
            pattern_scores = {"vector": 0, "matriz": 0, "cadena": 0, "estructura": 0}
            
            for type_name, patterns in self.patterns.items():
                matches = []
                for pattern in patterns:
                    found = re.findall(pattern, code, re.IGNORECASE)
                    if found:
                        matches.extend(found)
                        pattern_scores[type_name] += len(found)
                
                if matches:
                    analysis["detected_patterns"][type_name] = matches
            
            # Buscar palabras clave en comentarios o cadenas
            for type_name, words in self.keywords.items():
                for word in words:
                    word_count = sum(1 for m in re.finditer(rf'\b{word}\b', code, re.IGNORECASE))
                    pattern_scores[type_name] += word_count * 0.5  # Menos peso que los patrones de código
            
            # Determinar el tipo basado en los puntajes
            if pattern_scores:
                max_type = max(pattern_scores.items(), key=lambda x: x[1])
                if max_type[1] > 0:
                    analysis["type"] = max_type[0]
            
            # Usar el nombre del archivo como indicador adicional si está disponible
            if filename:
                basename = os.path.basename(filename).lower()
                for type_name in self.patterns.keys():
                    if type_name in basename:
                        # Si el nombre del archivo sugiere un tipo, aumentar su puntaje
                        pattern_scores[type_name] += 2
                        # Reevaluar el tipo
                        max_type = max(pattern_scores.items(), key=lambda x: x[1])
                        if max_type[1] > 0:
                            analysis["type"] = max_type[0]
            
            # Calcular la complejidad basada en varios factores
            complexity = 0
            # Factor 1: Número de líneas de código
            if analysis["lines_of_code"] < 30:
                complexity += 10
            elif analysis["lines_of_code"] < 100:
                complexity += 30
            else:
                complexity += 50
            
            # Factor 2: Uso de estructuras de datos y conceptos avanzados
            if analysis["has_classes"] or analysis["has_structs"]:
                complexity += 20
            if len(analysis["functions"]) > 3:
                complexity += 15
            if pattern_scores["matriz"] > pattern_scores["vector"]:
                complexity += 10
            
            # Factor 3: Número de patrones detectados
            total_patterns = sum(len(patterns) for patterns in analysis["detected_patterns"].values())
            complexity += min(total_patterns * 2, 20)  # Cap at 20
            
            # Asegurar que la complejidad esté entre 0 y 100
            analysis["complexity"] = min(max(complexity, 0), 100)
            
            return analysis
            
        except Exception as e:
            print(f"Error al analizar código: {e}")
            traceback.print_exc()
            return {"error": str(e), "type": "default"}
    
    def analyze_description(self, text):
        """Analiza una descripción textual para determinar el tipo de ejercicio."""
        try:
            # Tokenizar y etiquetar el texto
            tokens = word_tokenize(text.lower())
            tagged = pos_tag(tokens)
            
            # Buscar palabras clave por tipo
            scores = {"vector": 0, "matriz": 0, "cadena": 0, "estructura": 0}
            
            for word, tag in tagged:
                # Solo considerar sustantivos y verbos
                if tag.startswith('N') or tag.startswith('V'):
                    for type_name, keywords in self.keywords.items():
                        if word in keywords:
                            scores[type_name] += 1
            
            # Determinar el tipo basado en los puntajes
            if scores:
                max_type = max(scores.items(), key=lambda x: x[1])
                if max_type[1] > 0:
                    return max_type[0]
            
            return "default"
            
        except Exception as e:
            print(f"Error al analizar descripción: {e}")
            traceback.print_exc()
            return "default"
