#include <catch2/catch_test_macros.hpp>

#include "client.h"
#include "table.h"
#include "club.h"
#include "club_util.h"
#include "day_logger.h"

TEST_CASE( "TestCaseClient" ) {
    Client c("bob"); // name - bob

    SECTION( "TestCheckStatus" ) {
        REQUIRE( c.check_status() == ClientStatus::ARRIVED );
    }

    SECTION( "TestWaiting" ) {
        c.waiting();

        REQUIRE( c.check_status() == ClientStatus::WAITING );
    }

    SECTION( "TestSitting" ) {
        c.sitting(1);

        REQUIRE( c.check_status() == ClientStatus::SITTING );
        REQUIRE( c.get_table_id() == 1 );
    }
}

TEST_CASE( "TestCaseTable" ) {
    Table t(1); // id - 1

    SECTION( "TestCheckStatus" ) {
        REQUIRE( t.check_status() == TableStatus::FREE );
    }

    SECTION( "TestClientSitting" ) {
        t.client_sitting("bob", "09:00"); // name - bob, time - 09:00

        REQUIRE( t.check_status() == TableStatus::OCCUPIED );
        REQUIRE( t.get_cur_client() == "bob" );

        SECTION( "TestClientStanding" ) {
            t.client_standing("10:00", 10); // time - 10:00, money per hour - 10

            REQUIRE( t.check_status() == TableStatus::FREE );
            REQUIRE( t.get_cur_client() == "" );
            REQUIRE( t.current_info() == "1 10 01:00" );
        }
    }
}

TEST_CASE( "TestCaseClub" ) {
    Club c(2, "09:00", "15:00", 10); // tables - 2, time opened - 09:00, time closed - 15:00, money per hour - 10

    SECTION( "TestCorrectClientArriving" ) {
        c.client_arriving("bob", "09:10"); // name - bob, time - 09:10
        c.client_arriving("alice", "10:00"); // name - alice, time - 10:00

        REQUIRE( c.get_count_clients_in_club() == 2 );
        REQUIRE( c.is_client_arrived("bob") == true );
        REQUIRE( c.is_client_arrived("alice") == true );
    }

    SECTION( "TestIncorrectClientArriving" ) {
        c.client_arriving("bob", "08:20"); // name - bob, time - 08:20

        REQUIRE( c.get_count_clients_in_club() == 0 );
        REQUIRE( c.is_client_in_club("bob") == false );
    }

    SECTION( "TestCorrectClientSitting" ) {
        c.client_arriving("bob", "09:10"); // name - bob, time - 09:10
        c.client_arriving("alice", "10:00"); // name - alice, time - 10:00
        c.client_arriving("eva", "10:10"); // name - eva, time - 10:10

        c.client_sitting("bob", "10:00", 1);

        REQUIRE( c.is_client_sitting("bob") == true );
        REQUIRE( c.get_tables_free() == 1 );
        REQUIRE( c.get_table_id_by_client("bob") == 1 );
        REQUIRE( c.get_client_by_table_id(1) == "bob" );

        c.client_sitting("alice", "11:00", 2);

        REQUIRE( c.is_client_sitting("alice") == true );
        REQUIRE( c.get_tables_free() == 0 );
        REQUIRE( c.get_table_id_by_client("alice") == 2 );
        REQUIRE( c.get_client_by_table_id(2) == "alice" );

        c.client_leaving("bob", "11:30");
        c.client_sitting("eva", "11:40", 1);

        REQUIRE( c.is_client_sitting("eva") == true );
        REQUIRE( c.get_tables_free() == 0 );
        REQUIRE( c.get_table_id_by_client("eva") == 1 );
        REQUIRE( c.get_client_by_table_id(1) == "eva" );
    }

    SECTION( "TestIncorrectClientSitting" ) {
        c.client_arriving("bob", "09:10"); // name - bob, time - 09:10
        c.client_arriving("alice", "10:00"); // name - alice, time - 10:00

        c.client_sitting("bob", "10:00", 1);
        c.client_sitting("alice", "10:10", 1);

        REQUIRE( c.is_client_sitting("alice") == false );
        REQUIRE( c.get_table_id_by_client("bob") == 1 );
        REQUIRE( c.get_client_by_table_id(1) == "bob" );
    }

    SECTION( "TestCorrectClientWaiting" ) {
        c.client_arriving("bob", "09:10"); // name - bob, time - 09:10
        c.client_arriving("alice", "10:00"); // name - alice, time - 10:00
        c.client_arriving("eva", "10:10"); // name - eva, time - 10:10

        c.client_sitting("bob", "10:00", 1);
        c.client_sitting("alice", "11:00", 2);
        c.client_waiting("eva", "11:01");

        REQUIRE( c.is_client_in_queue("eva") == true );
        REQUIRE( c.get_count_clients_in_queue() == 1 );
        REQUIRE( c.get_table_id_by_client("eva") == 0 );
        REQUIRE( c.get_first_client_in_queue() == "eva" );

        c.client_leaving("bob", "11:30");

        REQUIRE( c.is_client_in_queue("eva") == false );
        REQUIRE( c.get_count_clients_in_queue() == 0 );
        REQUIRE( c.get_table_id_by_client("eva") == 1 );
        REQUIRE( c.get_client_by_table_id(1) == "eva" );
    }

    SECTION( "TestIncorrectClientWaiting" ) {
        c.client_arriving("bob", "09:10"); // name - bob, time - 09:10
        c.client_waiting("bob", "09:11");

        REQUIRE( c.get_count_clients_in_queue() == 0 );
        REQUIRE( c.get_table_id_by_client("bob") == 0 );
        REQUIRE( c.is_table_free(1) == true );
    }

    SECTION( "TestCorrectClientLeaving" ) {
        c.client_arriving("bob", "09:10"); // name - bob, time - 09:10
        c.client_arriving("alice", "10:00"); // name - alice, time - 10:00

        c.client_leaving("alice", "11:00");

        REQUIRE( c.get_count_clients_in_club() == 1 );
        REQUIRE( c.is_client_in_club("alice") == false );

        c.client_sitting("bob", "11:10", 1);
        c.client_leaving("bob", "11:40");

        REQUIRE( c.get_count_clients_in_club() == 0 );
        REQUIRE( c.is_client_in_club("bob") == false );
    }
}
