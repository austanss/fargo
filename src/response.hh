#pragma once

namespace fargo {

    enum Status : unsigned long {
        FLAWLESS            = 0,
        REDUNDANT           = 1,
        QUIET_FAILURE       = 2,
        ERROR_UNKNOWN       = 3,
        ERROR_MISUSE        = 4,
        ERROR_UNIMPLEMENTED = 5,
        ERROR_STATE_CORRUPT = 6,
        ERROR_MISALLOCATION = 7,
        ERROR_FAILED_INIT   = 8,
    };

    class StatusValidator 
    {

    public:
        inline static bool indicates_intervention(const Status status) { return (status != Status::FLAWLESS && status != Status::QUIET_FAILURE ); }

    };

    template <typename Treturn>
    class Response 
    {
    public:
        Response() : status(Status::FLAWLESS), result(Treturn()) {}
        Response(const Status status, const Treturn& value) : status(status), result(value) {}
        Response(const Response<Treturn>& other) : status(other.status), result(other.result) {}
        ~Response() {}

        Status status;
        Treturn result;
    };

    // Specialization for void
    template <>
    class Response<void>
    {
    public:
        Response() : status(Status::FLAWLESS) {}
        Response(const Status status) : status(status) {}
        Response(const Response<void>& other) : status(other.status) {}
        ~Response() {}

        Status status;
    };

    // Shorthands
    class Responses
    {

    public:
        static Response<void> flawless() { return Response<void>(Status::FLAWLESS); }
        static Response<void> redundant() { return Response<void>(Status::REDUNDANT); }
        static Response<void> problematic() { return Response<void>(Status::ERROR_UNKNOWN); }
        static Response<void> quiet_failure() { return Response<void>(Status::QUIET_FAILURE); }

    // Intentionally unimplemented
    private:
        Responses();
        ~Responses();

    };

}
