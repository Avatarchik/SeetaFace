aux_source_directory (. SRC_LIST)

message(${SRC_LIST})

# add external libraries
find_package(OpenCV REQUIRED)

enable_testing ()
link_directories(/home/kissy-64/Desktop/SeetaFaceEngine-master/FaceIdentification)
foreach (f ${SRC_LIST})
  string(REGEX REPLACE "[.]cpp" ".bin" BIN ${f})
  add_executable(${BIN} ${f})
  target_link_libraries(${BIN} seeta_facedet_lib seeta_fa_lib viplnet seeta_facedet_lib seeta_fa_lib ${OpenCV_LIBS})
endforeach ()

