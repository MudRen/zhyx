//                ��׼��������ʾ��                                   |
// �þ�����Ʒ  ����֮��(������������б�)
// by naihe 8:34 03-10-30 ï��
// ��Ϊ������Ʒ�������ǿ��� hj_room1.c ���ٵõ���ʿJOB��
// ����ֻ���ɸ���ұ��������ڵ��ϻ��ƽ�������ң������Զ������

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name( HIB"����֮��"NOR, ({ "youling ling", "ling" }) );
    set("long", "����һ������������ƣ�������������ɢ�������ص���Ϣ������Ī����\n");
    set("waiting_set",1);
// ����ʱҪ delete �����ã�����ᷢ������

    set("unit", "��");
    set("hj_game/obj", "yl_ling");
    set("value", 1);
    set_weight(100);
    setup();
}

void init()
{
    remove_call_out("check_environment");
    if( !query("no_check") ) call_out("check_environment", 1);
}

void check_environment()
{
    object env;

    if( query("waiting_set") ) return;
    env = environment(this_object());

    if( !query("my_master")
      || query("my_master")->query_temp("this_time_mark") != query("this_time_mark")
      || !env || env != query("my_master") )
    {
        remove_call_out("delete_me");
        remove_call_out("check_environment");
        set("no_check",1);
        call_out("delete_me", 1);
    }
}

void delete_me()
{
    message_vision( "$N���ط���һ������֮������ʧ�����ˡ�\n", this_object());
    destruct(this_object());
}

