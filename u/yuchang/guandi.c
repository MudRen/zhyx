//�ص��� writed by yuchang

#include <ansi.h>
inherit ROOM;
#define MAX_EXP 20000000
#define MAX_SCO 200000
int check_name(string name,object me);
void create()
{
        set("short", "�ص���");
        set("long", @LONG
    ���������ݳ��ڵĹص���ʱ����һЩ��������������ǩ���ˣ�
�����ܳ��һ����ǩ������һ��������ҵ��������ж�������һ��ص�
��(xiang)�����Ȼ������������봴�����Ļ���ȥ���ǩ(qiuqian)
������������ɡ�
LONG);
        set("item_desc", ([
                "xiang" :
        "�۾���תʲô��Ҫ��ǩ�Ϳ�㡣\n"
        ]));
        set("exits",([ /* sizeof() == 1 */
                "east":"/d/city/wumiao",
        ]));

        set("no_fight",1);

        setup();
}

void init()
{
       add_action("do_qiuqian","qiuqian");
       add_action("do_kaibang","kaibang");
       if( time()-query("last_time")>600)
       delete("qiuqian"); 

}

int do_qiuqian()
{
       object me=this_player(),ob=this_object();

       if(!objectp(me) || !interactive(me) ) return 1;

       if(me->query("banghui"))
       {
          tell_object(me,"���Ѿ���"+me->query("banghui/name")
                      +"�����ˣ��ѵ��뱳��ԭ���İ�᣿\n");
          return 1;
       }

       if(me->query("combat_exp") < MAX_EXP)
       {
          tell_object(me,RANK_D->query_respect(me)+"��ʵս���黹��"+
                      (string)(MAX_EXP-me->query("combat_exp"))
                      +"�㣬�޷��������ᡣ\n");
          return 1;
       }

       if(me->query("score") < MAX_SCO)
       {
          tell_object(me,RANK_D->query_respect(me)+"���ۺ����ۻ���"+
                      (string)(MAX_SCO-me->query("score"))
                      +"�㣬�޷��������ᡣ\n");
          return 1;
       }

       if(me->query("more_money") < 1)
       {
          tell_object(me,RANK_D->query_respect(me)+"������������Ҫһ�����ƽ�"
                      +"����Ŀ�ϵ�Ǯ��������\n");
          return 1;
       }

       if( ob->query("qiuqian/"+me->query("id")) )
       return notify_fail("���Ѿ����ǩ�ˣ��´��������������ɣ�\n");

       if( me->query_temp("qiuqian") )
       return notify_fail("���Ѿ�����ǩ�ˣ����ĵ����ǩ�����ɣ�\n");

       ob->set("qiuqian/"+me->query("id"),1);
       ob->set("last_time",time());
       message_vision("$N����һ���㣬������Ĭ���������"+me->name()+
       "Ը�������ɣ����������������ص�ү\n�͸��������գ����˴�ҵ��"+
       "���ս���һͳ�����ӱظж����£����ܹص�ү����\n",me);

       me->set_temp("qiuqian",1);
       me->start_busy(10+random(2));
       call_out("qian_out",10,me);
       return 1;
}

void qian_out(object me)
{
      string msg;
      int time;
      string date;

      if(!objectp(me) || environment(me) != this_object() )
      return;

      me->delete_temp("qiuqian");

      msg = "��ž����һ����һö��ǩ��$N����ǰ��$N��æ��ǩʰ"+
            "��һ����ֻ��ǩ��д����\n";
      if( random(me->query("kar")) > random(30-me->query("kar")) )
      {
        time = ( uptime()+random(1000)+1000 )*365;
        date = CHINESE_D->chinese_date(time);
        me->set_temp("create_time",date);
        msg += HIY"\n        "+date+"\n"+NOR;
      } else
       msg +=  HIW"\n        "+"ʱ��δ�ã������˽�\n"NOR;

      message_vision(msg,me);
      return;
}

int do_kaibang(string arg)
{
       object me=this_player(),lingpai;

       if(!objectp(me) || !interactive(me) ) return 1;

       if(! me->query_temp("create_time") )
       return notify_fail("����������ʲô����ǩ��û���Ҫ���ﰡ��\n");

       if(me->query("more_money") < 1)
       {
          tell_object(me,RANK_D->query_respect(me)+"������������Ҫһ�����ƽ�"
                      +"����Ŀ�ϵ�Ǯ��������\n");
          return 1;
       }

       if( me->query_temp("create_time") != NATURE_D->game_time() )
       return notify_fail("ʱ��δ���أ����ż�ʲôѽ��\n");

       if(!arg)
       return notify_fail("����kaibang <�����> ������ᡣ\n");

       if(! check_name(arg,me)) return 1;

       me->delete_temp("create_time");

       lingpai=new(__DIR__"obj/lingpai");
       lingpai->create(arg);
       lingpai->set("bangzhu",me->query("name"));
       lingpai->set("bangzhu_id",me->query("id"));
       lingpai->set("player",([me->query("id"):me->query("name")]));
       lingpai->set("npc",([]));
       lingpai->set("area",([]));
       lingpai->set("money",0);
       lingpai->save();
       destruct(lingpai);
       me->add("more_money",-1);
       me->set("banghui/name",arg);
       me->set("banghui/rank","����");
       me->set("banghui/rank_lv",9);
       me->save();

       message("channel:rumor",HIC"\n����ᴫ�š�"+me->query("name")+
               "�ɹ�������"+arg+"�������²���������⣿��\n" NOR,users());

       return 1;
}

int check_name(string name,object me)
{
        int i;

        i = strlen(name);

        if(file_size("/data/guild/"+name+".o")!=-1)
        {
                tell_object(me,"�ǳ���Ǹ������İ����������ˡ�\n");
                return 0;
        }

        if( (strlen(name) < 4) || (strlen(name) > 8 ) )
        {
                tell_object(me,"��������붨�ڶ����ĸ���֮�䡣\n");
                return 0;
        }
        while(i--)
        {
               if( name[i]<=' ' )
               {
                        tell_object(me,"�Բ�����İ�����в����ÿ����ַ���\n");
                        return 0;
               }
               if( i%2 == 0 && !is_chinese(name[i..<0]) )
               {
                        tell_object(me,"���á����ġ�������İ�ᡣ\n");
                        return 0;
               }
        }
        return 1;
}


