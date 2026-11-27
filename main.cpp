#include <iostream>
#include "PgManage.h"


int main() {

    PgManage pg;

    // 1. Add rooms
    std::cout << "\n===== ROOM MANAGEMENT =====\n";

    pg.addRoom(101, "Double", 4000, 2);
    pg.addRoom(102, "Single", 7000, 1);

    pg.displayAvailableRooms();

    // 2. Register tenant
    std::cout << "\n===== TENANT MANAGEMENT =====\n";

    pg.addTenant("Prince", "9876543210", 101);

    pg.displayTenants();

    // 3. Create November rent record
    std::cout << "\n===== RENT MANAGEMENT =====\n";

    pg.createRentRecord(
        1001,
        "2026-11-01",
        "2026-11-30",
        "2026-11-05",
        4000
    );

    // 4. Add partial payment
    std::cout << "\n===== FIRST PAYMENT =====\n";

    pg.addRentPayment(
        1001,
        2000,
        "2026-11-05",
        "UPI"
    );

    // 5. Add remaining payment
    std::cout << "\n===== SECOND PAYMENT =====\n";

    pg.addRentPayment(
        1001,
        2000,
        "2026-11-10",
        "Cash"
    );

    // 6. Display rent and payment history
    std::cout << "\n===== PAYMENT HISTORY =====\n";

    pg.displayRentHistory(1001);

    // 7. Create December rent record
    std::cout << "\n===== NEXT MONTH RENT =====\n";

    pg.createRentRecord(
        1001,
        "2026-12-01",
        "2026-12-31",
        "2026-12-05",
        4000
    );

    pg.displayRentHistory(1001);

    std::cout << "\n===== PENDING RENT REPORT =====\n";

    pg.displayPendingRent();
    return 0;
}
