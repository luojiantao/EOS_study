#!/bin/bash
  
for args in $@
do
echo $args
break
done

eos_path=$args

cp $eos_path/CMakeModules ./ -rf
cp $eos_path/libraries ./ -rf
cp $eos_path/externals ./ -rf
cp $eos_path/contracts ./ -rf
cp ./ENV/appbase_comp.camke.in  ./libraries/appbase/CMakeLists.txt
