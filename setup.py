from distutils.core import setup, Extension


sentiment_module = Extension('_sentiment',
						   extra_compile_args=['-std=c++14', "-O3", "-fopenmp"],
                           sources=['sentiment_wrap.cxx', 'sentiment.cpp'],
                           extra_link_args=['-lgomp', '-lboost_chrono', '-lboost_filesystem', '-lboost_system'],)

setup (name = 'sentiment',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig example from docs""",
       ext_modules = [sentiment_module],
       py_modules = ["sentiment"],
      ) 