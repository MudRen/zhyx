// Ů���/������Ů���յص�

#include <ansi.h> 
inherit ROOM;

#define XUANYIN    "/u/yuchang/special/xuannv/xuanyin.h"
#define XUANNVJIAN       "/u/yuchang/special/xuannv/xuannvjian.h"
#define SPECIAL     "/data/item/"

void create()
{
	set("short", "Ů���");
	set("long", @LONG
�˴������������Ů洡��ഫ�̹ſ���ٵغ�Ů�������
�������Σ����������������������������˽��ɴ˶���������Ů
洸������ʯ������֮ȱ�ڣ����䷽��������Ϳ֮̿�١�������
�������޲�����Ů����˲���֮�£����������ʾ���⡣�ഫ��
Ů洱ӻ�֮���ڴ����ߵ��(ketou)����������
LONG );
	set("exits", ([		
		"south"        : "/d/changan/road6",
	]));
	set("objects",([	
             __DIR__"statue" : 1,
	]));
       set("no_fight",1);	
	setup();	
}

void init()
{
    add_action("do_ketou", "ketou");  
    add_action("do_tuotai", "tuotai");      
}

int do_ketou()
{
     object me, xuanyin, xuannvjian;
     string fn, fc, answer;     

     me = this_player();
    
     if (me->is_busy() || me->is_fighting())
     {
            write("��æ������˵�ɣ�\n");
            return 1;
     }
     if (me->query("jing") < 20)
     {
            write("�㾫�����㣡\n");
            return 1;
     }
     if (me->query("jing") > 20) 
          me->add("jing", -20);
     else me->set("jing", 1);

     me->start_busy(2 + random(2));

     message_vision(HIC "ֻ��$N" HIC "�泯Ů����񣬹��ڵ��Ϲ�����������������ͷ��\n\n"
                    NOR, me);

     message_vision(HIC "��ͷ��ϣ�$N����վ��������\n\n" NOR, me);  

     if ( me->query("special_skill/emperor")
          || me->query("special_skill/lonely") )
     {
         tell_object(me, HIW"������ԼԼ�ƺ�����Ů��������˵���������������ӻ�֮�ˣ�\n"
                         "���ض����ˡ�\n\n"NOR);
         return 1;
     }

     if (! me->query("special_skill/queen") )
     {
         tell_object(me, HIR"�����в�����̾���Լ���Ѱ��֮�������޻۸������ڴ��������\n"
                         "ȴ��֪��Ů��Ƿ��������Ӧ�أ�\n\n"NOR);
         return 1;
     }

     if (  me->query("xuannv/item") &&  me->query("xuannv/tuotai")  )
     return notify_fail(HIG"������ԼԼ�ƺ�����Ů��������˵��������֪��֮�ϣ�\n"
                        "���������ڴ��˷ѹ�������찴������ɴ������֮�书��\n�����У�"
                        "����(canwu)���(linghui)����������Ů�٣�\n\n"NOR);      
    
     if (random(10) == 1)
     {            
         if (  ! me->query("xuannv/item") )
         {       
             message_vision(HIY "\n��Ȼֻ��Ů���һ��������������������죬\n"
                            "$N��ͷ֮���漴�ѿ�һ������ӡ�\n$Nһ�����㲻�ȣ���ʱ"
                            "������ȥ��\n\n"NOR, me);  
             me->set("xuannv/item", 1);

           //�������ɴ
           fc = read_file(XUANYIN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIG "������ɴ�������ȴ��Ӳ�ޱȣ�"
                               "ͨ��ɢ���ŵ�����ϼ�⡣\n������Լ�����������Ů" 
                               "�����轣��ͼ�����ƺ�������һ\n�ż�Ϊ�����Ľ�����"
                               "��Ե֮�˲����ɴ������ѧ��ʲô��\n"NOR 
                           HIC "����ɴ�Ͽ���һ��С�֣�Ů洴��ھ�����Ů" 
                               + me->query("name") +
                              "(" + me->query("id") + ")��\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));          

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-xuanyin";

           if (file_size(fn + ".c") > 0)
           {
                if (xuanyin = find_object(fn)) destruct(xuanyin);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           xuanyin = load_object(fn);
           xuanyin->move(__DIR__"cave");
           me->set("can_summon/xuanyin",fn);
         
           //�����Ů��
           fc = "";
           fc = read_file(XUANNVJIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIR "����Ů洴��ھ�����Ů����������"
                               "����������һ�㵭����ϼ�⡣\n" HIW
                              "�����Ͽ���һ��С�֣�Ů洴��ھ�����Ů" 
                               + me->query("name") +
                              "(" + me->query("id") + ")��\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-xuannvjian";

           if (file_size(fn + ".c") > 0)
           {
                if (xuannvjian = find_object(fn)) destruct(xuannvjian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           xuannvjian = load_object(fn);

           xuannvjian->set("owner/" + me->query("id"), 5000000);
           xuannvjian->set("magic/imbue",50);

           xuannvjian->move(__DIR__"cave");
           me->set("can_summon/xuannvjian",fn);        
            
           me->move(__DIR__"cave");
           return 1;     
         }
 
      // ��̥����,�����츳
       if (  ! me->query("xuannv/tuotai") )
           {   
               message_vision(WHT"Ů洱�$N���ĸж������ֳ����ʵ���\n�������ڴ�ߵ��?"
                               "�����ж������츳����?��\n\n"NOR, me);
                            
                write(HIG"Ů洴���һ����̥���ǵĻ��ᣬ�������µ��������츳��\n"NOR
                      HIR"������̥���Ǻ���ǰ���ӵ���������ȫ����Ч��\n"
                      "ʵս���鼰һ�м���ȫ����������������ˣ�"NOR HIY
                      "\n��ش�(Y/N)\n" NOR);
		  input_to("do_yes", answer);               
           }
 
     }  
     return 1;                   
}

int do_yes(string answer)
{   
   object me;
   me = this_player();
   if ( answer == "Y" || answer == "yes" || answer == "y" )
   { 	
   	me->set_temp("xuannv/tuotai/ask",1);

       write(HIG"�ðɣ���Ȼ�������Ѿ�����������·���80���츳��\n"
                "���������ڵ���13��С�ڵ���30,\n"
                "ָ����tuotai <����> <����> <����> <��>\n"NOR);
     	
   } else
   {            
   	write("�ðɣ��ı�����Ļ���ʱ������\n");
   }
   return 1;	
}

int do_tuotai(string arg)
{
    object me;
    int tmpstr, tmpint, tmpcon,tmpdex;
    string answer;

    me = this_player();
    if	( ! me->query_temp("xuannv/tuotai/ask") ) return 0;
    if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
                return notify_fail(HIG"ָ���ʽ��tuotai <����> <����> <����> <��>\n"NOR);
 
    if( tmpstr<13) return notify_fail("����ѡ���������������С��13��\n");
    if( tmpint>30) return notify_fail("����ѡ������Բ������ܴ���30��\n");
    if( tmpint<13) return notify_fail("����ѡ������Բ�������С��13��\n");
    if( tmpcon>30) return notify_fail("����ѡ��ĸ��ǲ������ܴ���30��\n");
    if( tmpcon<13) return notify_fail("����ѡ��ĸ��ǲ�������С��13��\n");
    if( tmpdex>30) return notify_fail("����ѡ������������ܴ���30��\n");
    if( tmpdex<13) return notify_fail("����ѡ�������������С��13��\n");
    if((tmpstr+tmpint+tmpcon+tmpdex)>80) 
    return notify_fail("����ѡ��Ĳ����ܺͲ��ܴ���80��\n");
    write(HIC "ָ���츳Ϊ ����:" + tmpstr + " ����:" + tmpint + " ����:" +
          tmpcon + " ��:" + tmpdex + "��������\n"NOR 
          HIY"��ش�Y/N��\n" NOR, me);

    me->set_temp("/xuannv/tuotai/str",tmpstr);
    me->set_temp("/xuannv/tuotai/int",tmpint);
    me->set_temp("/xuannv/tuotai/con",tmpcon);
    me->set_temp("/xuannv/tuotai/dex",tmpdex);

    input_to("do_yes2", answer);
    return 1;
}

int do_yes2(string answer)
{
   object me;
   mapping my, my_sk;
   string skills_name;

   me = this_player();
   my = me->query_entire_dbase();
   my_sk = me->query_skills();

   if ( answer == "Y" || answer == "yes" || answer == "y" )
   { 	 	
      message_vision(HIY "ֻ��һ��ϼ��������$N���ڣ�$N��ʱ�е�ͷʹ���ѣ�"   
                         "�಻���ԡ�\n"NOR, me);

        my["str"] = me->query_temp("/xuannv/tuotai/str");
        my["int"] = me->query_temp("/xuannv/tuotai/int");
        my["con"] = me->query_temp("/xuannv/tuotai/con");
        my["dex"] = me->query_temp("/xuannv/tuotai/dex");
       	me->set("combat_exp", 0);           
		me->set("max_neili",0);
		me->set("neili",0);
		me->set("max_jingli",0);
		me->set("jingli",0);
		me->set("max_qi",100);
		me->set("eff_qi",100);
		me->set("qi",100);
		me->set("max_jing",100);
		me->set("eff_jing",100);
		me->set("jing",100);
              me->set("mud_age",0);
              me->set("age", 14);
              me->set("shen",0);
              me->delete("breakup");
              me->delete("animaout");

  		foreach(skills_name in keys(my_sk))
	      {
		   me->delete_skill(skills_name);
             }
             me->delete("gift");
             me->delete_temp("xuannv");     
             me->set("xuannv/tuotai",1);
             me->unconcious();
             me->set("potential", me->query_potential_limit() );
   } else
   {
   	  write("��������ѡ���츳��\n");
   }
   return 1;		

}





