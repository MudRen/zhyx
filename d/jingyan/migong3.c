#include <room.h>
#include <ansi.h>
inherit ROOM;

void random_exit();

void create()
{
        set("short", "�����");
        set("long", @LONG
   ����������һ�����ǽ�Ͽ�������
��Щ�������͸߹�,�ֹ�ϸ�¾��ţ����̾����Ӵ�
���������ѽ⣬���Ķ���Щ�������������ʶ��
�㣬�������ϵ��������޾�һ��Ҳû������������
��֮����
LONG );
                set("item_desc", ([       
"����" : "�㷢�ָ����е㰼͹��ƽ����������Ŀ��Ĳ�죬
�ػᵱ��ʯ�ƺ��Թ�ȥ,�㲻���밴��(an)����!\n",  
                          ]));
              set("no_stab", 1); 
       set("exits", ([
                "west" :"d/jingyan/migong2",                                           
                                                ]));
                set("no_clean_up", 0);
        setup();
} 
void init()
{
  object me = this_player();
        add_action("do_an", "an");
        add_action("do_la", "la"); 
        add_action("do_zhuan", "zhuan");
}
void check_longtou()
{
    object me;
    me = this_player();
if(query("longtou")==6)
{
   message_vision(HIC"ͻȻ����͹�˳�����������{la)��һ��!!��\n"NOR, this_player());
      me->set_temp("la_longtou",1);
remove_call_out("on_del");
call_out("on_del", 10);
}
}
int do_la(string arg)
{
        object me;
        me = this_player(); 
   if( !me->query_temp("la_longtou")) return 0;   
     if( !arg || arg=="" ) return notify_fail("��Ҫ��ʲô����!\n");
            if( arg=="����") {
             write(HIB"��һ�ѽ��������������� \n"NOR); 
         write(HIR"�����ƺ�����������ת��������ת�ıߺ���? \n"NOR); 
             me->delete_temp("la_longtou");             this_player()->set_temp("zhuan_longtou", 1);
             return 1;
       }
}
 int do_an(string arg)
{
        object zhu, me=this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="����" )
                             { 
if(query("longtou")<10)
{                                             message_vision(
HIC"$N�Ѹ����������ﰴ!\n"NOR, this_player());
add("longtou",1);
check_longtou();
return 1;
                }
delete("longtou");
 message_vision(HIG"�㰴��ͷ��,���������˻�ȥ!\n"NOR, this_player());
                return 1;
        }
        return 1;
}
int do_zhuan(string arg)
{
    object me; 
    object room;
    string dir;
             me = this_player();
 if (!me->query_temp("zhuan_longtou")) 
return 0;
      if( !arg || arg=="" ) return notify_fail("��Ҫתʲô����!\n");
      if( sscanf(arg, "%s", dir)==1 ) {
    if( dir=="left" ) {
   message_vision(HIC"$N�Ѹ�������ת��һת��\n"NOR, this_player()); 
            add("zhuanmen", 1); 
return 1;
}
 else if( dir=="right") {
         if (query("zhuanmen")) {   
                        message_vision(HIC"$N�Ѹ�����ת�˻�ȥ��\n"NOR, this_player()); 
                        message_vision(HIC"��������ԭλ����Ȼ����ǰ˿�����졣\n"NOR, this_player());
                        
                this_player()->delete_temp("zhuan_longtou"); 
                
                random_exit();
                        
room = load_object("/d/jingyan/migong5.c");
    message("vision", "�������������һЩ���أ���е�Ť�����𵴡�\n",me );
    message("vision", "ͻȻ����ǰ����9���󶴣���֪�����ĸ����ܽ����ܵ���\n",room ); 
        message("channel:chat", HIW"�����㹬��"+me->query("name")+"�ɹ����뾪�㹬�ܵ���!!\n"NOR,users());
                call_out("on_guanmen", 180);
}
}
return 1;
        }
        else {
            write("����ת���ĸ�����?\n");
            return 1;
        }
}
void on_guanmen(object room)
{ 
      if( room = find_object("/d/jingyan/migong5.c") ) 
            room->delete("exits/1");
            room->delete("exits/2");
            room->delete("exits/3");
            room->delete("exits/4");
            room->delete("exits/5");
            room->delete("exits/6");
            room->delete("exits/7");
            room->delete("exits/8");
            room->delete("exits/9");
delete("longtou");  
 message_vision(HIG"ͻȻ�������ǵ���������������ʧ��!\n"NOR, room);
}

void on_del()
{
  object me = this_player();

if (!me) return 0;

if (environment(me)!=this_object())
{
delete("longtou");
remove_call_out("on_del");
return 0;
}
  call_out("on_del", 10);
}

void random_exit()
        {
                object room = load_object("/d/jingyan/migong5.c");
        
                int *a = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
                int x = random(9) + 1;
                
                if (! room)
                        return 0;//û�������
                
                room->set("exits/"+x , "/d/jingyan/lev1/dong01");
                a -= ({x});
                
                for( int i = 0; i < 8;i++)
                        room->set("exits/"+a[i], "/d/city/wumiao");      
                        
                        //return x;//����ֵΪͨ���ܵ��������ֵ
                        return;
        }

