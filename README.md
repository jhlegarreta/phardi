# README #



### Requirements ###

* Armadillo 
* ITK 4.9
* GCC 4.9
* OpenBLAS (for multicore parallelism)
* LaPack

### How do I get set up? ###


```
#!bash

mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/g++-4.9 -DCMAKE_BUILD_TYPE=Release
make
```

### Execution ###


```
#!bash

USAGE: phardi [options]

Options:
Compulsory arguments (You MUST specify ALL arguments):
  --data, -k         Data file
  --mask, -m         Binary mask file
  --bvecs, -r        b-vectors file
  --bvals, -b        b-values file
  --odf, -o          Output path

Optional arguments (You may optionally specify one or more of):
  --precision, -p    Calculation precision (float|double)
  --iterations, -i   Number of iterations (default 300)
  --lambda1          Longitudinal diffusivity value, in units of mm^2/s (default 0.0017)
  --lambda2          Radial diffusivity value, in units of mm^2/s (default 0.0003)
  --lambda-csf       Diffusivity value in CSF, in units of mm^2/s (default 0.0030)
  --lambda-gm        Diffusivity value in GM, in units of mm^2/s (default 0.0007)
  --verbose, -v      Verbose execution details
  --help, -h         Print usage and exit

Examples:
 phardi -k /data/data.nii.gz -m /data/nodif_brain_mask.nii.gz -r /data/bvecs -b /data/bvals --odf /result/ 
```
