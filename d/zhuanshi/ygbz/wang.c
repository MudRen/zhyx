// yuchang /2006/1/15/
#include <ansi.h> 
inherit ROOM;


void create()
{
        set("short", "����");
        set("long", @LONG 
����һ������,���������Զ,�����ѳ����ฯ�����,
��Ȼ���Ժ����׵���(zheng)��, ���������Ǹ��޵׶�, 
���ܶ��Ǹֱ�!���Ŵ����ƺ��������ػζ�(huang)��
LONG
        );
       set("no_fight",1);
       setup();
}

void init()
{
                
    add_action("do_piao", "huang"); 
    add_action("do_zheng", "zheng");
}

int do_piao(string arg)
{
    object me; 
    me = this_player();

    if( !arg || arg != "wang" )
    { 
       write("����Ҫ�ζ�(wang)��\n");
       return 1;
    }
    message_vision("$Nʹ���ζ���������������Ʈ����\n\n", me);

    me->set_temp("piaowang", 1);
    return 1;
}
     
int do_zheng(string arg)
{
    object me;
    me = this_player();

    if (!arg || arg != "wang" ) 
       return notify_fail("����Ҫ����(wang)��\n");
 
    if (me->query_temp("piaowang") ) 
    {
       message_vision(HIY"$Nʹ����������������ѡ�\n\n"NOR, me);
       message_vision(HIB"$N����������������ƣ�������֮��"
            "���ɵ����ְ�������ȥ��\n$N�ɹ������ڸְ�"
            "���԰�͹�ұڵĶ��ڴ���\n\n"NOR, me);
       me->delete_temp("piaowang"); 
       me->move(__DIR__"qiangbi");
       return 1;
    }
    else 
      message_vision(HIY"$Nʹ��������������ʼ����˿������\n"
                    "�ƺ�Ӧ����(huang)���¡�\n\n"NOR, me);
    return 1;
}
    