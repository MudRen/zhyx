#include <ansi.h>
#include <command.h>;

inherit ROOM;

void create()
{
        set("short", "��ѻ��");
        set("long", @LONG
һ������֦��ɵĴ��񳲣�����ľ��Ų�����ѻ�������ƺ�����ѻר��
���ĳ�����ͣ������ѻ�ɽ���ЪϢ��ͬʱҲ�в�����ѻ�ɵ�������ʳ����
�񳲵�����һ����Ȼ�γɵ�ʯ��(dong)���ƺ������������ȥ������ʯ��
ͨ�������ֻ����ѻ��֪���ˡ�
LONG
        );
        
        
        set("sleep_room",1);
	set("objects",([
	]));

set("exits", ([ /* sizeof() == 1 */
//    "south" : "/u/kyy/rose",
//    "west" : __DIR__"dmyuan2",
]));
        setup();
}

void init()
{
        add_action("do_zuan", "zuan");
        add_action("do_fei", "fei");
        add_action("do_check","jiuyang");
        add_action("do_sleep","shuijiao");
        add_action("do_test","test");
}

int do_check(string arg)
{
         object obj;
         if (!arg) 
         {
                 obj = "/adm/daemons/story/jiuyang"->select_character();
                 if (obj) 
                 {
                         write(obj->query("id")+"\n");
			return 1;
                 }
                 return notify_fail("û��\n");
         }
         obj = find_player(arg);
         if (!obj) return notify_fail("����˲����ߡ�\n");
         if (SKILL_D("jiuyang-shengong")->valid_learn(obj)) return notify_fail("����˿���ѧ��\n"); 
         return notify_fail("����˲�����ѧ��\n");
}
int do_zuan(string arg)
{
   object me;
   me = this_player();
   if ( !arg )
   {
      message_vision("�����ʲô��\n",me);
      return 1;
   }

   if (arg == "dong") 
   {
        message_vision("$Nû�б�İ취���룬ֻ��è�������ʯ�����档\n",me);
        me->start_busy(1);
        message_vision("$N��֪���˶�ã�ֻ����ǰһ�������������档\n",me);
        me->start_busy(1);
        me->move("/d/city/guangchang");
        return 1;
   }

}

int do_fei(string arg)
{
        object me;
        me = this_player();
        if ((string)me->query("id") != "smallfish")
        return notify_fail("���г����\n");
        
        message_vision("$N���ĳ������ˡ�\n",me);
        me->move("d/city/kedian");
        return 1;
}

int do_sleep(string arg)
{
        object me;
        me= this_player();
//      if ((time()-me->query("last_sleep"))<0)
//        return notify_fail("���˯��һ�����Ȼ��ɡ� \n");
        message_vision("$N����ѻ����һ�ɣ����Ժ�����˯���ˡ�\n",me);
        me->set_temp("sleeped",1);
        me->set_temp("block_msg/all",1);
        me->set("last_sleep",time());
        me->set("no_get", 1);
        me->set("no_get_from", 1);
        me->disable_player("<˯����>");
        call_out("wakeup",0,me);
        return 1;
}
void wakeup(object me)
{
        if(!me) return;
        me->set("qi",    2*me->query("eff_qi"));
        me->set("jing",  2*me->query("eff_jing"));
        me->set("jingli", 2*me->query("eff_jingli"));
        me->set("neili", 2*me->query("max_neili"));
        me->enable_player();
        call_out("del_sleeped", 0, me);
        message_vision("$N��һ����ѻ�Ľ��������ˡ�\n",me);
        me->set_temp("block_msg/all", 0);
        write("�㱻��ѻ�Ľ��������ˡ�\n");
        me->delete("no_get");
        me->delete("no_get_from");

}

void del_sleeped(object me)
{
        if (objectp(me) &&  me->query_temp("sleeped"))
                me->delete_temp("sleeped");
}

int do_test()
{
        int i;
        string index,temp_index;
        object ob,me;
        me = this_player();
        ob = present("sword",me);
        if (objectp(ob))
                index = base_name(ob);

        temp_index = index;
        if (objectp(ob) && strlen(temp_index) > 21 && temp_index[0..20] == "/data/gaoshou/weapon/")
        {
                i = strsrch(temp_index,"-");
                if (i != -1) temp_index = temp_index[0..i-1];
                i = strsrch(temp_index,"/",-1);
                if (i != -1) temp_index = temp_index[i+1..strlen(temp_index)-1];
                if (temp_index && strlen(temp_index) > 1)
                        index = "/data/item/" + temp_index[0..0] + "/" + temp_index + "-" + ob->query("id");
        }
        if (file_size(index+".c") > 0)
                tell_object(me,index + "\n");
        return 1;
}
