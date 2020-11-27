// By yuchang@zhyx
#include <ansi.h> 
inherit ROOM;

void check_longtou();

void create()
{
        set("short", "Ծ����");
        set("long", @LONG  
�����ǳ���������Ծ����,���м�������ʯ����
�������������̽�����ʯ��ͷ(shi longtou)����
���㾦��Ϊʯ��ƽ������������
LONG); 
        set("item_desc", ([       
"shi longtou" : "������һȦ������Բ��������ĽӺۣ���������Ŀ��Ĳ�죬
�ػᵱ��ʯ�ƺ��Թ�ȥ,�㲻���붥һ��(ding)Ȧ��(quan hen)��\n",          
        ]));
        set("exits", ([
               "west" : "/d/changan/ca13",
        ]));
        set("no_clean_up", 0);
        setup();
} 

void init()
{
        add_action("do_ding", "ding");
        add_action("do_ba", "ba"); 
        add_action("do_zhuan", "zhuan");
}

int do_ding(string arg)
{
    object zhu, me = this_player();

    if ( !arg || arg != "quan hen" )  
       return notify_fail("��Ҫ��ʲôѽ��\n");  
                                                  
       message_vision(HIR"$N����ͷ�·���Ȧ���������϶���һ��!\n"NOR, me);
       add("longtou",1);
       check_longtou();
       return 1; 
}

void check_longtou()
{
        object me;
        me = this_player();
        if (query("longtou") >= 6)
        {
            message_vision(HIC"$NͻȻ�о���ͷ���˺ܶ࣬"
                         "�ƺ����԰�(ba)������!��\n"NOR, me);
            me->set_temp("ba_longtou",1);
            delete("longtou");
        }
}

int do_ba(string arg)
{
        object me;
        me = this_player(); 
        if( ! me->query_temp("ba_longtou")) return 0;   

        if( !arg || arg != "shi longtou" && 
            arg != "longtou"  ) return notify_fail("��Ҫ��ʲô����!\n");
       
        message_vision(HIB"\n$Nһ�ѽ���ͷ���������� \n"NOR, me); 
        write(HIC"\n��ͷ�ƺ�����������ת��������ת�ıߺ���? \n\n"NOR); 

        me->delete_temp("ba_longtou");             
        me->set_temp("zhuan_longtou", 1);
        return 1;    
}



int do_zhuan(string dir)
{
    object me; 
    object room;
    me = this_player();

    if (!me->query_temp("zhuan_longtou")) 
        return 0;

    if (!dir || dir =="") 
        return notify_fail("��Ҫ���ĸ�����ת����ͷ!\n");
     
    if (dir == "left") 
    {
       message_vision(HIC"$N����ͷ����ת��һת��\n"NOR, me); 
       add("zhuanmen", 1); 
       return 1;
    }

    if (dir == "right") 
    {
        if (query("zhuanmen")) 
        {   
           message_vision(HIG"\n$N����ͷ��ת�˻�ȥ��\n"NOR, me); 
           message_vision(HIG"\n��������ԭλ����Ȼ����ǰ˿�����졣\n"NOR, me);
           me->delete_temp("zhuan_longtou"); 
           delete("zhuanmen");

           room = find_object(__DIR__"yuanzi");
           if (! room) room = find_object(__DIR__"yuanzi");
 
           room->set("exits/down", __DIR__"jindi");
           message_vision(HIR"�������������Ÿ�������һ��Ķ�����"
                           "$N�е�Ť�����𵴡�\n\n"NOR,me );
           tell_object(me, HIY"��֪������԰������ʲô����û�У�����ȥ��һ�¡�\n"NOR);

           tell_room(room, "ͻȻ�����ˮλ�½��˺ö࣬�����������ȥ�ˡ�\n");
 
           message("vision", HBRED"�����ش��š�" + me->query("name") + 
                          "�ɹ������������!\n"NOR,users());
           remove_call_out("close");
           call_out("close", 180, room);
        } else 
        message_vision(HIC"$N����ͷ����ת��һת��\n"NOR, me); 

        return 1;
     }
     else {
            write("��Ҫ���ĸ�����ת����ͷ?\n");
            return 1;
          }

}

void close(object room)
{     
     if ( room )
     { 
        room->delete("exits/down");
        delete("longtou");  
        message_vision(HIG"ͻȻ�������ǵ�������ˮλ������!\n"NOR, room);
     }
}

