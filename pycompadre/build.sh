#$PYTHON $SRC_DIR/update_conda_cmake.py $SRC_DIR/python/cmake_opts.txt.in $SRC_DIR/cmake_opts.txt
echo "Compadre_USE_MPI:BOOL=OFF" > $RECIPE_DIR/cmake_opts.txt
echo "PYTHON_EXECUTABLE=$PYTHON" >> $RECIPE_DIR/cmake_opts.txt
if [ "$OSX_ARCH" != "" ]; then
    echo "BLAS_LIBRARY_DIRS=/System/Library/Frameworks/Accelerate.framework//Versions/A/Frameworks/vecLib.framework/Versions/A/" >> $RECIPE_DIR/cmake_opts.txt
    echo "LAPACK_LIBRARY_DIRS=/System/Library/Frameworks/Accelerate.framework//Versions/A/Frameworks/vecLib.framework/Versions/A/" >> $RECIPE_DIR/cmake_opts.txt
fi
CMAKE_CONFIG_FILE=$RECIPE_DIR/cmake_opts.txt $PYTHON setup.py install
