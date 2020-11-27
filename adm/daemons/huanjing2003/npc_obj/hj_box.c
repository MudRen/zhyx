//                ��׼��������ʾ��                                   |
// ���þ�����ı���
// by naihe  2002-10-23  ��ï��

#include <ansi.h>

inherit ITEM;

#include "hj_settings/room_amount_hj.h"

string *color=({
    ""HIR"",
    ""HIW"",
    ""HIG"",
    ""HIC"",
    ""HIM"",
    ""HIB"",
    ""HIY"",
    ""HIY"",
});

void create()
{
    set_name( color[random(8)] +"����"NOR, ({"box","bao xiang","xiang"}));

    set_weight(10000000);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "һ��δ������(open)�ı��䡣\n");
        set("unit", "��");
        set("value", 0);
    }

    set("hj_game/obj","box");
    set("no_get","1");
    set("be_open","no");
    set("no_refresh",1); // ���ᱻ������¡�
    setup();
}

void init()
{
    add_action("do_open","open");
}

int do_open(string arg)
{
    string *obj_list=({
        "/clone/money/silver",
        __DIR__"hj_obj_quest",   // ����ʯ�������ܵ���Ʒ
        __DIR__"hj_obj_tools",   // �Ա���Ϸ�а�������Ʒ���綨��ˮ����
        __DIR__"hj_obj_weapon",  // �����͵���Ʒ
        __DIR__"hj_obj_other",   // ��Ʒ����ʯ��
        __DIR__"hj_obj_other",   // ��Ʒ����ʯ����ֵļ����ϵ�
    });

    object obj,me;
    int temp;
    string msg=""HIB"ֻ��һ������ð�𡭡������ƺ�����һЩʲô��"NOR"\n";

    me=this_player();
    temp=1+random(3); // ���ʱ��һ�����ӿɻ��3������

    if(arg!="box" && arg!="bao xiang" && arg!="xiang")
        return 0;

    if(query("be_open") == "yes")
        return notify_fail("��������ѱ��򿪹��ˡ�\n");

    if( me->is_busy() || me->query_temp("hj_need_waiting") )
        return notify_fail("�㻹æ���ء�\n");

    message_vision(CYN"$N"NOR+CYN"С�ĵذ�"+query("name")+NOR+CYN"���˿�����\n"NOR,me);
    me->start_busy(1);
    set("be_open","yes");
    set("long","��������Ѿ����򿪹��ˡ�\n");
    set_name(CYN"�򿪵ı���"NOR,({"box","bao xiang","xiang"}));


    // �ɱ����������ͳһ������
    while( temp-- )
    {
    // ��ʯ֮��Ψһ���֣��򿪱���ʱ�õ�����ʯ�ļ�������
        if( me->query_temp("hj_special/xs") && !random(3) )
            obj = new( __DIR__"hj_obj_quest" );
        else obj=new( obj_list[random(sizeof(obj_list))] );
        obj->move(environment(this_object()));
        message_vision(msg,this_object());
    }

    call_out("delete_me",30+random(31));
    return 1;
}

void delete_me()
{
    message_vision("$N������ʧ�����ˡ�\n",this_object());
    destruct(this_object());
}
