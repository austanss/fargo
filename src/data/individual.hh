#pragma once

namespace fargo {

    class Individual {

    public:
        // Constructor
        Individual();

        // Destructor
        ~Individual();

        struct {
            unsigned long   uid;
            unsigned long   index;
            unsigned long   age_days;

            struct {
                unsigned long   value_funds;
                unsigned long   value_assets;
                unsigned long   income_annual;
                unsigned long   welfare_annual;
            } finances;

            struct {
                bool            unassisted;
                bool            handicapped;
                bool            ssdi_applied;
                bool            sssi_applied;
                bool            unem_applied;
            } benefits;

            struct {
                unsigned long   child_count;
                bool            married;
                bool            masculine;
            } marital;

            struct {
                bool            frugal;
                bool            generous;
                bool            grateful;
                bool            healthy;
                bool            intelligent;
                bool            diligent;
            } character;

        } data;

    };

}
