if(EXISTS "C:/Users/Александр/Desktop/Bitarr/build/test/tests[1]_tests.cmake")
  include("C:/Users/Александр/Desktop/Bitarr/build/test/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
