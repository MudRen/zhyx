// #pragma optimize
// #pragma save_binary

inherit F_DBASE;

#include <ansi.h>

void create()
{
    seteuid(ROOT_UID);
    set("name", HIR "ϵͳ����" NOR);
    set("channel_id", "ϵͳ����");
    CHANNEL_D->do_channel(this_object(), "sys", "\n��������Ѿ�������\n");
    call_out("auto_clear", 30);
}

void auto_clear()
{
    CHANNEL_D->do_channel(this_object(), "sys", HIY "������������С�\n" NOR);
    if (random(3) == 1)
        rm("/log/usage");

    cp("/log/debug.log", "/driver/system.log"); //����debug.logΪsysterm.logΪ������
    remove_call_out("auto_clear");
    call_out("auto_clear", 1800); //30��������һ��
}
