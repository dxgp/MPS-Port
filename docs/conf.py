project = 'MetalPerformanceShaders C++'
copyright = '2023, Gunjan Payal'
author = 'Gunjan Payal'

# Extensions to use
extensions = [ "breathe" , "exhale"]

# Configuration for the breathe extension
# Which directory to read the Doxygen output from
breathe_projects = {"MPSCPP":"xml"}
breathe_default_project = "MPSCPP"

exhale_args = {
    "containmentFolder": "./api",
    "doxygenStripFromPath": "../metal-cpp/MetalPerformanceShaders",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "MetalPerformanceShaders C++ API",
    "exhaleDoxygenStdin":    "INPUT = ../metal-cpp/MetalPerformanceShaders/MPSCore ../metal-cpp/MetalPerformanceShaders/MPSMatrix"
}

# Configuration for the theme
# html_theme = "sphinx_book_theme"
html_theme = 'sphinx_rtd_theme'
# html_theme_options = {
#     "repository_url": "https://github.com/HappyCerberus/modern-documentation",
#     "use_repository_button": True,
# }