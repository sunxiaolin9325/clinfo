#ifndef TOOL
#define TOOL

#include <CL/opencl.h>
#include <stdlib.h>

//检测返回值是否正确
static void checkError(cl_int err)
{
    if(err!=CL_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }
}
#define CHECK_ERROR(err) (checkError(err))

//检测结果是否为空
#define CHECK_NULL(a) {if(a==NULL){exit(EXIT_FAILURE);}}

#endif // TOOL

