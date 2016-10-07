#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "mserver.h"
#include "mclient.h"

static void newClient_mserver_t_overflow(void **state)
{
    mserver_t *ms = mserver_new(1);
    int i=0;
    while(i<99)
    {
        mserver_newClient(ms);
        i++;
    }
    assert_int_equal(mserver_getStatus(ms), OVERFLOW_CLIENTS);
    mserver_free(ms);
}

static void new_mserver_t_wrongId(void **state)
{
    mserver_t *ms = mserver_new(-2);
    assert_int_equal(mserver_getStatus(ms), WRONG_ID);
    mserver_free(ms);
}

static void sendMessage_mclient_wrongAddress(void **state)
{
    mserver_t *ms = mserver_new(1);
    mserver_newClient(ms);
    mserver_newClient(ms);
    mclient_sendMessage(ms, mserver_getClient(ms, 0), 12, 12);
    mclient_t *mc = mserver_getClient(ms,0);
    assert_int_equal(mclient_getStatus(mc), WRONG_ADDRESS);
    mclient_free(mc);
    mserver_free(ms);
}

static void getClient_mserver_noClient(void **state)
{
    mserver_t *ms = mserver_new(1);
    mclient_t *mc = mserver_getClient(ms, 3);
    assert_int_equal(mserver_getStatus(ms), NO_CLIENT_WITH_THIS_ID);
    mclient_free(mc);
    mserver_free(ms);
}

static void sendMessage_mclient_wrongMessage(void **state)
{
    mserver_t *ms = mserver_new(1);
    mserver_newClient(ms);
    mserver_newClient(ms);
    mserver_newClient(ms);
    mclient_t *mc = mserver_getClient(ms, 0);
    mclient_sendMessage(ms, mc, 100, 2);
    assert_int_equal(mclient_getStatus(mc), WRONG_MESSAGE);
    mclient_free(mc);
    mserver_free(ms);
}

static void newClient_mserver_t_ClientOk(void **state)
{
    mserver_t *ms = mserver_new(1);
    mserver_newClient(ms);
    mserver_newClient(ms);
    assert_int_equal(mclient_getStatus(mserver_getClient(ms, 0)), CLIENT_OK);
    mserver_free(ms);
}


int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(newClient_mserver_t_overflow),
        cmocka_unit_test(new_mserver_t_wrongId),
        cmocka_unit_test(sendMessage_mclient_wrongAddress),
        cmocka_unit_test(getClient_mserver_noClient),
        cmocka_unit_test(sendMessage_mclient_wrongMessage),
        cmocka_unit_test(newClient_mserver_t_ClientOk)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
