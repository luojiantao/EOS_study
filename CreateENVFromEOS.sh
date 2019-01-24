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

current_path=`pwd`
ln -s ${current_path}/project ${current_path}/contracts/project
sed -i '/add_subdirectory(integration_test)/a\add_subdirectory(project)' ${current_path}/contracts/CMakeLists.txt

