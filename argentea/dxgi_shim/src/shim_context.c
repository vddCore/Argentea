#include "shim_context.h"

PShimContext ShimContext_Create(void) {
    PShimContext context = (PShimContext)malloc(sizeof(ShimContext));
    
    if (!context) {
        return NULL;
    }
   
    memset(context, 0, sizeof(ShimContext));
    
    return context;
}

void ShimContext_Destroy(PShimContext context) {
    if (context != NULL) {
        free(context);
    }
}