// ��ʶ�/�������ӽ��յص�

#include <ansi.h> 
inherit ROOM;

#define QINGTIAN    "/u/yuchang/special/tianzi/qingtian.h"
#define TIANZIJIAN       "/u/yuchang/special/tianzi/tianzijian.h"
#define SPECIAL     "/data/item/"

void create()
{
	set("short", "��ʶ�");
	set("long", @LONG
�˴�����̩ɽ������������һ����۹ۣ���ǰΪ�ŵǷ�̨
�������ʵ۷�������ʽ������������С���˵���������ڴ˳�
�Ŀ�ͷ(ketou) ������Ͷ��͡�̨����һ���ֱ�����˵�Ǻ���
����������Զ����һʯ�٣����顸����С���´�������������
����������������֮��������̨��
LONG );
	set("exits", ([
		"southdown" : "/d/taishan/nantian",
		"eastdown"  : "/d/taishan/riguan",
		"west"      : "/d/taishan/zhangren",
		"up"        : "/d/taishan/fengchan",
	]));
	set("objects",([
	//	"/d/taishan/npc/wei-shi2" : 3,
             __DIR__"wuzibei" : 1,
	]));
       set("no_fight",1);
	set("outdoors", "taishan");
	setup();
      
	//replace_program(ROOM);
}

void init()
{
    add_action("do_ketou", "ketou");  
    add_action("do_tuotai", "tuotai");      
}

int do_ketou()
{
     object me, qingtian, tianzijian;
     string fn, fc, answer;     
 
     me = this_player();

     if (! me->query("special_skill/emperor") )
     return notify_fail("����ֻ���������Ӳ���ߵ�ݣ�Ѱ������������ȥ��\n\n");
     if (  me->query("tianzi/item") &&  me->query("tianzi/tuotai")  )
     return notify_fail("�����Ѿ�֪����ĳ����ˣ������ٿ�ͷ�ˣ�\n\n");
    
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

     message_vision(HIC "$N" HIC "˵����������" + me->query("name") +
                        "�ڴ˳���ߵ�ݡ���\n\n" NOR, me);
     message_vision(HIC "ֻ��$N" HIC "�����Ϸ������ڵ��Ϲ���������������ͷ��\n\n"
                    NOR, me);
     me->start_busy(2 + random(2));

     if (random(100) < 2 )
     {
             message_vision(HIC "��ͷ��ϣ�$N����վ��������\n\n" NOR, me);             
             return 1;
     } 
     else 
     {     if (  ! me->query("tianzi/item") )
         {
            message_vision(HIY "ɲʱ��ֻ��������ֳ��ס��ƶ��ۣ���$NЦ����\n��������"
                           "������ļ��죬����ȷʵû��ѡ�����ģ�\n����ҵȱ�������ӱ�"
                           "�����������������Ͷ���ƶ��������������������\n\n" NOR, me);    
           me->set("tianzi/item", 1); //��¼���Ѿ��ù���Ʒ��

           //��������
           fc = read_file(QINGTIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIW "���Ż������Ѱ��������ɢ���������������������֣�"
                               "ʲôҲ�����塣\n" HIC
                              "����Ե�Ͽ���һ��С�֣����������������" 
                               + me->query("name") +
                              "(" + me->query("id") + ")��\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));          

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-qingtian";

           if (file_size(fn + ".c") > 0)
           {
                if (qingtian = find_object(fn)) destruct(qingtian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           qingtian = load_object(fn);
           qingtian->move(me, 1);
           me->set("can_summon/qingtian",fn);
         
           //������ӽ�
           fc = "";
           fc = read_file(TIANZIJIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIY "����������������������ӵ���������"
                               "����������һ���⡣\n" HIW
                              "�����Ͽ���һ��С�֣����������������" 
                               + me->query("name") +
                              "(" + me->query("id") + ")��\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" + 
                me->query("id") + "-tianzijian";

           if (file_size(fn + ".c") > 0)
           {
                if (tianzijian = find_object(fn)) destruct(tianzijian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           tianzijian = load_object(fn);


           tianzijian->set("owner/" + me->query("id"), 5000000);
           tianzijian->set("magic/imbue",50);

           tianzijian->move(me, 1);
           me->set("can_summon/tianzijian",fn); 

           message_vision(HIW "\nֻ��" HIC"�����" NOR HIW"��"NOR HIY"�������ӽ�" NOR
                          HIW"ˢ��һ���ɵ���$N���ϣ���\n\n" NOR, me);  
           return 1;
        }  
      // ��̥����,�����츳
       if (  ! me->query("tianzi/tuotai") )
           {                               
                message_vision(HIY "�׵�ͻȻ���ֳ������������ڴ�ߵ��?"
                               "�����ж������츳����?\n\n"NOR, me);
                write(HIR"�׵۴���һ����̥���ǵĻ��ᣬ�������µ��������츳��\n"
                      "������̥���Ǻ���ǰ���ӵ���������ȫ����Ч��\n"
                      "ʵս���鼰һ�м���ȫ����������������ˣ�Y/N\n\n" NOR);
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
   	me->set_temp("tianzi/tuotai/ask",1);

       write(HIG"�õģ���Ȼ�������Ѿ�����������·���80���츳��\n"
                "���������ڵ���13��С�ڵ���30,\n"
                "ָ����tuotai <����> <����> <����> <��>\n\n"NOR);
     	
   } else
   {            
   	write("�õģ��ı�����Ļ���ʱ������\n");
   }
   return 1;	
}

int do_tuotai(string arg)
{
    object me;
    int tmpstr, tmpint, tmpcon,tmpdex;
    string answer;

    me = this_player();
    if	( ! me->query_temp("tianzi/tuotai/ask") ) return 0;
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
          tmpcon + " ��:" + tmpdex + "��������Y/N��\n" NOR, me);

    me->set_temp("/tianzi/tuotai/str",tmpstr);
    me->set_temp("/tianzi/tuotai/int",tmpint);
    me->set_temp("/tianzi/tuotai/con",tmpcon);
    me->set_temp("/tianzi/tuotai/dex",tmpdex);

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
      message_vision(HIY "ֻ��һ�����������$N���ڣ�$N��ʱ�е�ͷʹ���ѣ�"   
                         "�಻���ԡ�\n\n"NOR, me);

        my["str"] = me->query_temp("/tianzi/tuotai/str");
        my["int"] = me->query_temp("/tianzi/tuotai/int");
        my["con"] = me->query_temp("/tianzi/tuotai/con");
        my["dex"] = me->query_temp("/tianzi/tuotai/dex");
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
              me->set("shen",0);
              me->delete("breakup");
              me->delete("animaout");
              me->set("mud_age",0);            
              me->set("age", 14);

  		foreach(skills_name in keys(my_sk))
	      {
		   me->delete_skill(skills_name);
             }
        me->delete("gift");
        me->delete_temp("tianzi");
        me->set("tianzi/tuotai",1);
        me->unconcious();        
        me->set("potential", me->query_potential_limit() );

   } else
   {
   	  write("��������ѡ���츳��\n");
   }
   return 1;		

}
