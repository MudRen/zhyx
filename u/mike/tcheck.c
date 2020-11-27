#include <ansi.h>

inherit F_DBASE;

object *use = users();

object *check()
{
        object *list;
        list = filter_array(users(), (: $1->query("rmb") > 0 :));
        return list;
}
