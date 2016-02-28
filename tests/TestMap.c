//
//  TestMap.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include <stdio.h>
#include "../src/control/Map.h"
#include <assert.h>

int main(){
    map_init();
    assert(map_elements[0].height == 20);
    map_render((void*)1,20);

}
