"""
Run from same directory as this file is in
Generates UserGemmClKernels.cc

Would be nice to use Jinja2 for this, but using print for now, for consistency
"""

kernelNames = []
# lets just read the kernel names from UserGemmClKernels.h:
ifile = open('UserGemmClKernels.h', 'r')
contents = ifile.read()
for line in contents.split('\n'):
    if line.find('cl_kernel') < 0:
        continue
    kernelName = line.split()[2].split(';')[0]  # probably not terribly un-fragile, but works for now
    kernelNames.append(kernelName)
ifile.close()

ofile = open('UserGemmClKernels.cc', 'w')

ofile.write('// GENERATED using create_user_gemm_cl_kernels.py\n')
ofile.write('\n')

ofile.write('#if defined( __APPLE__ ) || defined( __MACOSX )\n')
ofile.write('#include <OpenCL/cl.h>\n')
ofile.write('#else\n')
ofile.write('#include <CL/cl.h>\n')
ofile.write('#endif\n')
ofile.write('\n')

for kernelName in kernelNames:
    ofile.write('cl_kernel %s = NULL;\n' % kernelName)
ofile.write('\n')

ofile.write('void initUserGemmClKernels(void) {\n')

for kernelName in kernelNames:
    ofile.write('    if(%s != NULL) {\n' % kernelName)
    ofile.write('        clReleaseKernel(%s);\n' % kernelName)
    ofile.write('        %s = NULL;\n' % kernelName)
    ofile.write('    }\n')

ofile.write('}\n')
ofile.close()
