# #   -*- coding: utf-8 -*-
from pybuilder.core import use_plugin, init

use_plugin("python.core")
use_plugin("python.unittest")   # Para pruebas unitarias
use_plugin("python.flake8")     # Para análisis de estilo/código
use_plugin("python.coverage")   # Para medir cobertura de pruebas
use_plugin("python.distutils")  # Para empaquetado y distribución

# Información del proyecto
name = "pract3"
version = "1.0.0"
summary = "Cifrador de Vigenère con opción de módulo 27 y 191"
default_task = "publish"

# Configuración
@init
def set_properties(project):
    # Opciones de compilación / Python
    project.set_property("python.version", "3.12.11")  

    # Configuración de Flake8 (estilo de código)
    project.set_property("flake8_break_build", True)
    project.set_property("flake8_max_line_length", 100)

    # Configuración de cobertura
    project.set_property("coverage_break_build", False)
    project.set_property("coverage_threshold_warn", 70)
    project.set_property("coverage_threshold_fail", 50)

    # Archivos incluidos en el paquete final
    project.set_property("distutils_packages", ["pract3"])
    project.set_property("distutils_console_scripts", ["pract3 = pract3:main"])
