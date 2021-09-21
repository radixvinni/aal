cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)
project(MpeiAAL)
include(ExternalProject)

include_directories (../)

option (USE_MIRACL 
        "Static-link math functions provided by M.I.R.C.L?" OFF) 
option (USE_MSIEVE 
        "Static-link msieve library?" OFF) 
option (KGEN
        "Generate Karatsuba algorithm files?" OFF) 

option (GENERATE_BINDINGS 
        "Generate library bindings for Python using SWIG?" ON) 

set (HEADERS
		../AAF/AAL/Algorithms.h
		../AAF/AAL/BasicType.h
		../AAF/AAL/Converter.h
		../AAF/AAL/DecompositionManager.h
		../AAF/AAL/EllipticcurvesGF2.h
		../AAF/AAL/EllipticcurvesGF3.h
		../AAF/AAL/Ellipticcurves.h
		../AAF/AAL/FactorizationAlgorithms.h
		../AAF/AAL/HashClass.h
		../AAF/AAL/Hash.h
		../AAF/AAL/IntegerBinomEllipticcurves.h
		../AAF/AAL/IntegerBinom.h
		../AAF/AAL/Integer.h
		../AAF/AAL/KInteger.hpp
		../AAF/AAL/Matrix.h
		../AAF/AAL/NumberVector.h
		../AAF/AAL/PolynomGF2_m_4.h
		../AAF/AAL/PolynomGF2_mY_7.h
		../AAF/AAL/PolynomGF3.h
		../AAF/AAL/PolynomGF3_m_6.h
		../AAF/AAL/PolynomGF3_mY_9.h
		../AAF/AAL/PolynomGF3n6.h
		../AAF/AAL/PolynomGF7.h
		../AAF/AAL/PolynomGF7N.h
		../AAF/AAL/PolynomGF7_m_14.h
		../AAF/AAL/PolynomGF7_m14.h
		../AAF/AAL/PolynomGF7_m_2.h
		../AAF/AAL/PolynomGF7_mY_13.h
		../AAF/AAL/PolynomGF7_mY_26.h
		../AAF/AAL/PolynomGF7_mY_3.h
		../AAF/AAL/Polynom.h
		../AAF/AAL/PrimeTester.h
		../AAF/AAL/ProbingDivisionAlgorithmDecomposition.h
		../AAF/AAL/ProbingDivisionAlgorithmDecompositionThread.h
		../AAF/AAL/TableManager.h
		)
set (SOURCES 
		funTD.cpp
		../AAF/AAL/Converter.cpp
		../AAF/AAL/DecompositionManager.cpp
		../AAF/AAL/Ellipticcurves.cpp
		../AAF/AAL/EllipticcurvesGF2.cpp
		../AAF/AAL/EllipticcurvesGF3.cpp
		../AAF/AAL/FactorizationAlgorithms.cpp
		../AAF/AAL/HashClass.cpp
		../AAF/AAL/Hash.cpp
		../AAF/AAL/IntegerBinom.cpp
		../AAF/AAL/IntegerBinomEllipticcurves.cpp
		../AAF/AAL/Integer.cpp
		../AAF/AAL/Matrix.cpp
		../AAF/AAL/NumberVector.cpp
		../AAF/AAL/Polynom.cpp
		../AAF/AAL/PolynomGF2_m_4.cpp
		../AAF/AAL/PolynomGF2_mY_7.cpp
		../AAF/AAL/PolynomGF3.cpp
		../AAF/AAL/PolynomGF3_m_6.cpp
		../AAF/AAL/PolynomGF3_mY_9.cpp
#		../AAF/AAL/PolynomGF3n6.cpp
		../AAF/AAL/PolynomGF7.cpp
		../AAF/AAL/PolynomGF7N.cpp
		../AAF/AAL/PolynomGF7_m_14.cpp
		../AAF/AAL/PolynomGF7_m14.cpp
		../AAF/AAL/PolynomGF7_m_2.cpp
		../AAF/AAL/PolynomGF7_mY_13.cpp
		../AAF/AAL/PolynomGF7_mY_26.cpp
		../AAF/AAL/PolynomGF7_mY_3.cpp
		../AAF/AAL/PrimeTester.cpp
		../AAF/AAL/ProbingDivisionAlgorithmDecomposition.cpp
		../AAF/AAL/ProbingDivisionAlgorithmDecompositionThread.cpp
		../AAF/AAL/TableManager.cpp
		)
set (TESTSRC
		../CppUnitLite/Test.cpp
		../CppUnitLite/TestRegistry.cpp
		../CppUnitLite/TestResult.cpp
		../Dev_Project/CodeBlocks\ IDE\ Project/main.cpp
# AAL Tests
		../AAF/AALT/BasicTypeTests.cpp
		../AAF/AALT/DecompositionManagerTests.cpp
		../AAF/AALT/EllipticcurvesGF2Tests.cpp
		../AAF/AALT/EllipticCurvesGF3Tests.cpp
		../AAF/AALT/EllipticCurvesTests.cpp
#???		../AAF/AALT/HashTests.cpp
		../AAF/AALT/IntegerBinomEllipticCurvesTests.cpp
		../AAF/AALT/IntegerBinomTests.cpp
		../AAF/AALT/IntegerTests.cpp
		../AAF/AALT/KIntegerTests.cpp
		../AAF/AALT/MatrixTests.cpp
		../AAF/AALT/NumberVectorTests.cpp
		../AAF/AALT/PolynomGF2_m_4Test.cpp
#		../AAF/AALT/PolynomGF3n6Tests.cpp
		../AAF/AALT/PolynomGF3Tests.cpp
		../AAF/AALT/PolynomGF7Test.cpp
		../AAF/AALT/PolynomGF7NTests.cpp
		../AAF/AALT/PolynomTests.cpp
		../AAF/AALT/TestFoctarizationAlgorithms.cpp
		../AAF/AALT/TestPolynomGF2_mY_7.cpp
		../AAF/AALT/TestPolynomGF3_m_6.cpp
		../AAF/AALT/TestPolynomGF3_mY_10.cpp
		../AAF/AALT/TestPolynomGF7_m_14.cpp
		../AAF/AALT/TestPolynomGF7_m14.cpp
		../AAF/AALT/TestPolynomGF7_m_2.cpp
		../AAF/AALT/TestPolynomGF7_mY_13.cpp
		../AAF/AALT/TestPolynomGF7_mY_3.cpp
		../AAF/AALT/TestPrimeTester.cpp
		)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})
source_group ("CppUnitLite" FILES ${TESTSRC})

message("-- Files: ${SOURCES}")

enable_testing()
configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_library (AAL ${SOURCES})
add_executable (aaltest.exe ${TESTSRC})
target_link_libraries(aaltest.exe AAL)

#add_test (TestsRun aaltest.exe)
add_test (TestsPass aaltest.exe)

set_tests_properties (TestsPass
  PROPERTIES PASS_REGULAR_EXPRESSION "There were no test failures")

install (FILES ${HEADERS} DESTINATION include)
install (TARGETS AAL DESTINATION lib)

if (USE_MIRACL)
	ExternalProject_Add(miracl
	  PREFIX .
	#  URL http://www.certivox.com/wp-content/themes/certivox/res/miracl.zip
	#  URL http://www.shamus.ie/uploads/File/miracl3.zip
	#  GIT_REPOSITORY git://github.com/CertiVox/MIRACL.git
	  GIT_REPOSITORY git://github.com/radixvinni/MIRACL.git
    #UPDATE_COMMAND ""
	#  PATCH_COMMAND patch -t -N -p0 < ../../miracl.patch
	#  CONFIGURE_COMMAND cmake .
	#  BUILD_COMMAND make -C ..
	  INSTALL_COMMAND ""
	)
	
	add_library(imp_miracl dlopen.cpp) #note: linux only by now
	target_link_libraries(imp_miracl dl)
  add_dependencies(imp_miracl miracl)
	target_link_libraries(AAL imp_miracl)
endif (USE_MIRACL)

if (USE_MSIEVE)
	ExternalProject_Add(msieve
	  PREFIX .
	#  SVN_REPOSITORY https://msieve.svn.sourceforge.net/svnroot/msieve/trunk
	  SVN_REPOSITORY https://svn.code.sf.net/p/msieve/code/tags/1.53
	  CONFIGURE_COMMAND ""
	 # PATCH_COMMAND patch -t -N -p0 < ../../msieve.patch
	  BUILD_COMMAND make -C ../msieve all
	  INSTALL_COMMAND ""
	)
	add_library(imp_msieve STATIC IMPORTED)
  set_property(TARGET imp_msieve PROPERTY
                IMPORTED_LOCATION src/msieve/libmsieve.a)
  add_dependencies(imp_msieve msieve)
	include_directories (src/msieve/include)
	add_library (demo src/demo.c)
	find_package (Threads)
	target_link_libraries (demo imp_msieve ${CMAKE_THREAD_LIBS_INIT} gmp m z dl)
	target_link_libraries(AAL demo)
	
endif (USE_MSIEVE)

if (KGEN)
	ADD_EXECUTABLE(kgen.exe kgen.cpp)
	GET_TARGET_PROPERTY(K_GENERATOR_EXE kgen.exe LOCATION)
	# add the custom command that will generate karatsuba files
	ADD_CUSTOM_COMMAND(
	   OUTPUT ../AAF/AAL/karatsuba64.hpp
	   COMMAND ${K_GENERATOR_EXE} 64 > ../AAF/AAL/karatsuba64.hpp
	   DEPENDS kgen.exe
	   #MAIN_DEPENDENCY 
	   )
	# now create an executable using the generated files
	add_custom_target(kgen DEPENDS ../AAF/AAL/karatsuba64.hpp)
  add_dependencies(AAL kgen)
  add_dependencies(kgen kgen.exe)
endif (KGEN)

if (GENERATE_BINDINGS)
	FIND_PACKAGE(SWIG REQUIRED)
	INCLUDE(${SWIG_USE_FILE})

	FIND_PACKAGE(PythonLibs)
	INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

	SET(CMAKE_SWIG_FLAGS "")

	SET_SOURCE_FILES_PROPERTIES(AAL.i PROPERTIES CPLUSPLUS ON)
	SWIG_ADD_MODULE(AAL python AAL.i)
	SWIG_LINK_LIBRARIES(AAL ${PYTHON_LIBRARIES} AAL)
endif (GENERATE_BINDINGS)

if (MSVC)
	add_definitions (/W0)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions (-w -fPIC -std=c++0x)
endif (MSVC)

ADD_CUSTOM_TARGET(ChangeLog
	        COMMAND svn update
	        COMMAND svn log > ChangeLog
)

