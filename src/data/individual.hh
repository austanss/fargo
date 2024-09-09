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
            unsigned long   age_years;

            struct {
                unsigned long   value_funds;
                unsigned long   value_assets;
                unsigned long   income_annual;
                unsigned long   welfare_annual;
            } finances;

            bool            unassisted;
            bool            wealthy;
            bool            handicapped;
            bool            unemployed;

            struct {
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