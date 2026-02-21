#include "iec_std_lib.h"
#include "iec_types_all.h"
#include "POUS.h"


void MAIN_init__(MAIN *data__, BOOL retain) {
  __INIT_VAR(data__->M001,__BOOL_LITERAL(FALSE),retain)
  __INIT_LOCATED(BOOL,__IX0_6,data__->X001,retain)
  __INIT_LOCATED_VALUE(data__->X001,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_2,data__->Y001,retain)
  __INIT_LOCATED_VALUE(data__->Y001,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_7,data__->X002,retain)
  __INIT_LOCATED_VALUE(data__->X002,__BOOL_LITERAL(FALSE))
}

// Code part
void MAIN_body__(MAIN *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,M001,,(!(__GET_LOCATED(data__->X002,)) && (__GET_VAR(data__->M001,) || __GET_LOCATED(data__->X001,))));
  __SET_LOCATED(data__->,Y001,,__GET_VAR(data__->M001,));

  goto __end;

__end:
  return;
} // MAIN_body__() 





