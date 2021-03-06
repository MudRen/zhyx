// edit.c
// updated by doing
#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;
void create()
{
        seteuid(getuid());
        set("name", "编辑指令");
        set("id", "edit");            
        set("channel_id",HIW"在线编辑");
}

int main(object me, string file)
{
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! file)
                return notify_fail("指令格式：edit <档名>\n");

        if (! me->is_admin())
        {
                switch (SECURITY_D->query_site_privilege("edit"))
                {
                case "all":
                        break;

                default:
                        return notify_fail("你不能编辑这个文件。\n");
                }
        }

        if (in_edit(me))
                return notify_fail("你已经在使用编辑器了。\n");

        seteuid(geteuid(me));
        file = resolve_path(me->query("cwd"), file);
        me->set("cwf", file);
        me->edit_file(file);
        CHANNEL_D->do_channel(this_object(),"sys",me->query("name")+"("+me->query("id")+")"+"正在编写"+file+"。");

        log_file("static/edit", sprintf("%s %-9s edit %s from %s.\n",
                                        log_time(),
                                        geteuid(me), file,
                                        query_ip_name(me)));
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : edit <档名>, edit here

利用此一指令可直接在线上编辑档案。

该命令在可以被授权使用的信息包括：enable。
HELP );
        return 1;
}


