#include "iec_std_lib.h"
#include "accessor.h"
#include "POUS.h"

void MAIN_init__(MAIN *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__QX0_2,data__->Y001,retain)
  __INIT_LOCATED_VALUE(data__->Y001,__BOOL_LITERAL(FALSE))
}

// Code part
void MAIN_body__(MAIN *data__) {
  // Initialise TEMP variables

  __SET_LOCATED(data__->,Y001,,!(__GET_LOCATED(data__->Y001,)));

  goto __end;

__end:
  return;
} // MAIN_body__() 





