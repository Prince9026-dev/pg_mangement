
#include <iostream>
#include "PgManage.h"

int main() {

    PgManage pg;

    // 1. Add rooms
    pg.addRoom(101, "Double", 4000, 2);
    pg.addRoom(102, "Single", 7000, 1);

    // 2. Display available rooms
    pg.displayAvailableRooms();

    // 3. Register tenant
    pg.addTenant("Prince", "9876543210", 101);

    // 4. Display tenants
    pg.displayTenants();

    // 5. Update tenant room
    pg.updateTenantRoom(1001, 102);

    // 6. Display updated tenant
    pg.displayTenants();

    // 7. Checkout tenant
    pg.checkoutTenant(1001);

    // 8. Display tenants again
    pg.displayTenants();

    return 0;
}
