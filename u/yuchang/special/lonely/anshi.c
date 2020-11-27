// ����Ů�����ڰ���

#include <ansi.h> 
inherit ROOM;

#define POTIAN      "/u/yuchang/special/lonely/potian.h"
#define CHIJIAN     "/u/yuchang/special/lonely/chijian.h"
#define SPECIAL     "/data/item/"

string look_wall();

string* skill = ({
        "strike",
        "parry",
        "force",        
        "sword",        
        "china-aojue",
});

void create()
{
	set("short", "����"); 
	set("item_desc",([
		"wall"	  :  (: look_wall :),
              "zhuan"  :  "һ��ͻ����שͷ���ƺ��е�Ź֡���֪��"
                          "(push)һ��������\n",
              "deng"   :  "һյ���͵ƣ���֪���ܲ��ܵ���(dian deng)��\n",	
	]));
       set("no_fight",1);
   //    set("no_sleep_room",1); 
       set("no_ride",1);       		
	setup();	
}

void init()
{		
     add_action("do_dian","dian");  
     add_action("do_canwu","canwu");  
     add_action("do_linghui","linghui"); 
     add_action("do_push","push"); 
              
}

int do_dian(string arg)
{
    object corpse, potian, chijian;
    string fn, fc, answer;     
    object me = this_player();

    if ( ! arg || arg != "deng")
       return notify_fail("��Ҫ��ʲô��\n");
    if ( query("light") ) 
       return notify_fail("���Ѿ������ˣ�\n");
    set("light",1);
    message_vision("$N�������͵ƣ������������˵���ߡ���������ϸ�������\n", me);
   
    if ( me->query("special_skill/lonely") &&
        ! me->query("lonely/item") )
    {
             me->set("lonely/item", 1);
           corpse = new(__DIR__"corpse");

           //��������

           fc = read_file(POTIAN);         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIG "���Ż��׵���۸�һ�㲼�²�û������𣬵�ȴ��Ӳ"
                                   "�ޱȣ�\n����������\n"NOR 
                               HIC "������Ͽ���һ��С�֣����������ɷ����" 
                               + me->query("name") +
                              "(" + me->query("id") + ")��\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-potian";

           if (file_size(fn + ".c") > 0)
           {
                if (potian = find_object(fn)) destruct(potian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           potian = load_object(fn);
           potian->move(corpse);
           me->set("can_summon/potian",fn);
         
           //��óལ
           fc = "";
           fc = read_file(CHIJIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIR "������ɷ����ר�õ�������"
                               "����������һ�㵭����Ѫ�⡣\n" HIW
                              "�����Ͽ���һ��С�֣����������ɷ����" 
                               + me->query("name") +
                              "(" + me->query("id") + ")��\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" + 
                me->query("id") + "-chijian";

           if (file_size(fn + ".c") > 0)
           {
                if (chijian = find_object(fn)) destruct(chijian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           chijian = load_object(fn);

           chijian->set("owner/" + me->query("id"), 5000000);
           chijian->set("magic/imbue",50);
         
           chijian->move(corpse);
           me->set("can_summon/chijian",fn);  

          //�����̥������
          new(__DIR__"wan")->move(corpse);  
            
          corpse->move(this_object());

    }
    return 1;
}

int do_canwu(string arg)
{             
        object me = this_player();
        int cost;
        int i;
        
        if (! arg || arg != "wall")
                return notify_fail("��Ҫ����ʲô��\n");

        if (! query("light") )
                return notify_fail("�������һƬɶ���������������ɶӴ��\n");

        if (! me->query("special_skill/lonely"))
                return notify_fail("�������ô���㲻��ǽ���ϵļ���ʲô��˼��\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (me->is_fighting())
                return notify_fail("���޷���ս����ר�������ж���֪��\n");      

        cost = 50 + random(50);
        if (me->query("jing") > cost)
        {
                for (i = sizeof(skill); i > 0; i--)
                {
                        if (me->query_skill(skill[i-1], 1) < 180 &&
                            me->can_improve_skill(skill[i-1]))
                        {
                                me->improve_skill(skill[i-1], 5 + random(30));
                        }
                }
                write(sprintf("�����ǽ�������ص��ܼ����ƺ��е��ĵá�\n"));
                me->receive_damage("jing", cost);
        } else
        {
                me->set("jing", 0);
                write("�����ڹ���ƣ�룬�޷�ר����������\n");
        }
        return 1;
}

int do_linghui( string arg )
{
    object me = this_player();

   if (! me->query("special_skill/lonely"))
       return 0;

   if (! query("light") )
       return notify_fail("�������һƬɶ��������������ɶӴ��\n");  
  
    if (me->is_busy())
          return notify_fail("��������æ���ء�\n");

    if (me->is_fighting())
          return notify_fail("�㻹���ȴ������˵�ɣ�\n");

    if ( ! arg || ( arg != "�����л�" && arg != "��������" 
         &&  arg != "�л�����") )
          return notify_fail("��Ҫ���ʲô���У���ʽΪ(linghui ����)��\n");

    if ( arg == "�����л�" 
        && me->query("can_perform/china-aojue/zhangzhen"))
          return notify_fail("�����㲻���Ѿ�������\n");
  
    if ( arg == "��������" 
        && me->query("can_perform/china-aojue/jianqi"))
          return notify_fail("�����㲻���Ѿ�������\n");

    if ( arg == "�л�����" 
        && me->query("can_perform/china-aojue/aojue"))
          return notify_fail("�����㲻���Ѿ�������\n");

    if ((int)me->query("jing") < 100)
          return notify_fail("��ľ����޷����У��޷������У�\n");
 
    me->receive_damage("jing", 90);

    me->start_busy(2 + random(4));

    if (random(10) == 1 && arg == "�����л�" )
    {
        me->add("china-aojue/zhangzhen/count", 1);

        if (me->query("china-aojue/zhangzhen/count") >= 10)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ�������л�����\n" NOR);

            me->set("can_perform/china-aojue/zhangzhen", 1);
            me->delete("china-aojue/zhangzhen/count");

            if (me->can_improve_skill("strike"))
                    me->improve_skill("strike", 1500000);
            if (me->can_improve_skill("china-aojue"))
                    me->improve_skill("china-aojue", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "��ԡ������л������������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(10) == 1 && arg == "��������" )
    {
        me->add("china-aojue/jianqi/count", 1);

        if (me->query("china-aojue/jianqi/count") >= 10)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ��������������\n" NOR);

            me->set("can_perform/china-aojue/jianqi", 1);
            me->delete("china-aojue/jianqi/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("china-aojue"))
                    me->improve_skill("china-aojue", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "��ԡ��������������������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(15) == 1 && arg == "�л�����")
    {
        me->add("china-aojue/aojue/count", 1);

        if (me->query("china-aojue/aojue/count") >= 20)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ���л���������\n" NOR);

            me->set("can_perform/china-aojue/aojue", 1);
            me->delete("china-aojue/aojue/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("strike"))
                    me->improve_skill("strike", 1500000);
            if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
            if (me->can_improve_skill("china-aojue"))
                    me->improve_skill("china-aojue", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "��ԡ��л����������������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }
         return notify_fail("����ͼ��ǽ������йء�" + arg + "�������ݣ�\n"
                           "�������ûʲôЧ������������������\n");

}


string look_wall()
{     
     if ( query("light") )	
     return
    WHT"��������������������������������������������\n"
	"��������������������������������������������\n"
	"�������������������л�����  ����������������\n"
	"��������������������������������������������\n"
	"��������������ƽ��ϰ��ѧ֮�����Ѿ�  ��������\n"
	"�������������ڴ˴���Ȼδ����Ӧ��ɷ  ��������\n"
	"����������֮��֮��������ʵ������䡡��������\n"
	"���������������⡣������������Ե��  ��������\n"
	"�������������˲��򣬾���������裬  ��������\n"
	"��������������ӱؽ�߳�彭��������  ��������\n"
	"����������һ����ʦ��Ȼ��ɷ����֮�¡���������\n"
	"�����������ſ���ּ�����֪��......����������\n"
	"��������������������������������������������\n"
	"������������������    ��Ӣ�ۡ�����  ��������\n"
	"������������������   ������ˡ����� ��������\n"
	"��������  (ָ��Ϊcanwu��linghui)   ��������\n"
	"��������������������������������������������\n"NOR;
    else
      return "�������һƬ��ɶҲ��������\n";
}

string long() 
{ 
       if ( query("light"))
          return "���Ż찵�ĵƹ⣬�㿴��ǽ�����ƺ�����һЩ�Źֵ���\n�֣�"
                 "�����Ǻ���ѧ�йء����̲�ס����ϸ����(look wall)��\n";
       else
           return "����һƬ��ڣ����ֲ�����ָ��ɶҲ��������\n"
                  "ǽ����Լ��յ���͵�(deng)��ǽ��Ҳ��һ��"
                  "ͻ��\n��שͷ(zhuan)��\n";
} 

int do_push(string arg)
{
        object room, me;

        me = this_player();

        if (! arg || arg != "zhuan" )
        {
		write("��Ҫ��ʲô��\n");
              return 1;        
        }
        message_sort(HIY"\n$N�ߵ�ǽ�ߣ���������һ��ͻ����ש�顣"
                     "\n" NOR, me);

        message_sort(HIY"\nͻȻǽ��һ�����������¶��һ���󶴣�\n"
                     "���������ͨ����硣"
                     "\n\n" NOR, me);
        set("exits/out", __DIR__"floor5");

        if (room = find_object(__DIR__"floor5"))
        {
        	room->set("exits/enter", __FILE__);
           	message("vision", HIY "\nǽ�ں�Ȼ����������������"
                        "¶��һ��ͨ����\n" NOR, room );
        }
        remove_call_out("close_andao");
        call_out("close_andao", 5);
        return 1;
}

void close_andao()
{
    	object room;
        int i;

        if (! query("exits/out")) return;
    		message("vision", HIY "\nֻ��ƹ��һ���죬ש���Զ�"
                        "�ƻ�ԭ��������Ҳ��֮��ʧ�ˡ�\n" NOR, this_object());

    	if (room = find_object(__DIR__"floor5"))
    	{
              room->delete("exits/enter");
        	message("vision", HIY "\nֻ��ƹ��һ���죬����"
                        "���Զ�����ʵʵ�ع���������\n" NOR, room);
    	}
    	delete("exits/out");
}







