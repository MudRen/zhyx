//��սʤ��(ת��npc ������Χ)

#include <ansi.h>
inherit  NPC;
int ask_wash();

void create()
{
	set_name("�����", ({ "sun wukong", "sun" }));
	set("title", HIY "��սʤ��" NOR);
	set("nickname", HIW "��̥����" NOR);
	set("gender", "����");
	set("age", 3000);
	set("long", @LONG
һ�Ż�ɫ�Ĺ�â������Ȼ͸��һ�ˣ�ϸ��ȴ���ܲ�׽�������Ρ�
LONG );
        set("gender", "����" );
        set("age", 3000);
        set("attitude", "friendly");
        set("max_neili", 100000);
        set("neili", 100000);
        set("max_jing", 100000);
        set("jing", 100000);
        set("max_qi", 100000);
        set("qi", 100000);
        set("jingli", 100000);
        set("max_jingli", 100000);
        set("str", 200);
        set("int", 200);
        set("con", 200);
        set("dex", 200);
        set("combat_exp", 99999999);

        set("inquiry", ([ 
            "��̥����" : (: ask_wash :), 
        ])); 

        set_skill("unarmed", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
	set_skill("force", 2000);

        set("jiali", 1000);

        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/armor", 3000); 

        setup();
        carry_object("d/city/obj/jiasha")->wear(); 
}


void init()
{
    add_action("do_ketou", "ketou");
    add_action("do_tuotai", "tuotai");  
}

int ask_wash()
{    
    object me = this_player();
    if (me->query("mark/sun_wash")) //�Ѿ�ϴ�����ж�
    {
       command("xixi " + me->query("id"));        
       return 1;
    }
    me->set_temp("sun/reborn/ask1",1);
    command("look " + me->query("id"));
    command("say �����С���޲�ת���İɣ�");    
    command("say �����ж������츳������");
    tell_object(me, HIW"������������˵����"
                    "����ҿĸ�ͷ(ketou)�ȣ�\n"NOR);   
    return 1;
}

int do_ketou()
{
    object me = this_player();
    string answer;
    if (! me->query_temp("sun/reborn/ask1") ) return 0; //��û����!

    if (! me->query("reborn") ) //û��ת�����ж�
      {
       command("kok " + me->query("id"));        
       command("say ����ҵ��ң��ú�������ת����������");
       return 1;
      }

    if (me->query("mark/sun_wash")) //�Ѿ�ϴ�����ж�
      {
       command("xixi " + me->query("id"));        
       return 1;
      }
     me->delete_temp("sun/reborn/ask1");
     message_vision(WHT"�������ƤЦ���Ķ�$N˵����\n�����ӿɽ�Ҳ����\n"NOR, me);                
     write(HIG"����մ���һ����̥���ǵĻ��ᣬ�������µ��������츳��\n"NOR
           HIR"������̥���Ǻ���ǰ���ӵ���������ȫ����Ч��\n"
              "ʵս���鼰һ�м���ȫ����������������ˣ�"NOR HIY
             "\n��ش�(Y/N)\n" NOR);
     input_to("do_yes", answer);
     return 1;
}


int do_yes(string answer)
{   
   object me;
   me = this_player();
   if ( answer == "Y" || answer == "yes" || answer == "y" )
   {
       me->set_temp("sun/reborn/ask2",1);	//ͬ��ϴ��
       write(HIG"�õģ���Ȼ�������Ѿ�����������·���126���츳��\n"
                "���������ڵ���13��С�ڵ���40,\n"
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
    if	(!me->query_temp("sun/reborn/ask2")) return 0;
    if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
                return notify_fail(HIG"ָ���ʽ��tuotai <����> <����> <����> <��>\n"NOR);

    if( tmpstr>40) return notify_fail("����ѡ��������������ܴ���40��\n");
    if( tmpstr<13) return notify_fail("����ѡ���������������С��13��\n");
    if( tmpint>40) return notify_fail("����ѡ������Բ������ܴ���40��\n");
    if( tmpint<13) return notify_fail("����ѡ������Բ�������С��13��\n");
    if( tmpcon>40) return notify_fail("����ѡ��ĸ��ǲ������ܴ���40��\n");
    if( tmpcon<13) return notify_fail("����ѡ��ĸ��ǲ�������С��13��\n");
    if( tmpdex>40) return notify_fail("����ѡ������������ܴ���40��\n");
    if( tmpdex<13) return notify_fail("����ѡ�������������С��13��\n");
    if((tmpstr+tmpint+tmpcon+tmpdex)>126) 
    return notify_fail("����ѡ��Ĳ����ܺͲ��ܴ���126��\n");
    write(HIC "ָ���츳Ϊ ����:" + tmpstr + " ����:" + tmpint + " ����:" +
          tmpcon + " ��:" + tmpdex + "��������Y/N��\n" NOR, me);

    me->set_temp("/sun/reborn/str",tmpstr);
    me->set_temp("/sun/reborn/int",tmpint);
    me->set_temp("/sun/reborn/con",tmpcon);
    me->set_temp("/sun/reborn/dex",tmpdex);

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

		me->set("mark/sun_wash", 1);//ϴ���¼
	        my["str"] = me->query_temp("/sun/reborn/str");
        	my["int"] = me->query_temp("/sun/reborn/int");
	        my["con"] = me->query_temp("/sun/reborn/con");
	        my["dex"] = me->query_temp("/sun/reborn/dex");

		//����Ե��ļ�¼
                me->set("gift/str/all",0),
                me->set("gift/str/succeed",0),
                me->set("gift/str/fail",0),
                me->set("gift/int/all",0),
                me->set("gift/int/succeed",0),
                me->set("gift/int/fail",0),
                me->set("gift/con/all",0),
                me->set("gift/con/succeed",0),
                me->set("gift/con/fail",0),
                me->set("gift/dex/all",0),
                me->set("gift/dex/succeed",0),
                me->set("gift/dex/fail",0),
		//���ǰ���еĹ���
                me->delete("gift/feng");
                me->delete("gift/lighting");
                me->delete("gift/water");
                me->delete("gift/sun");
		//������ɼ�¼
              //me->add("detach/" + me->query("family/family_name"), 1);
                me->delete("family");
                me->set("gongxian", 0);
                me->delete("quest");
                me->delete_temp("quest");
                me->set("title", "��ͨ����");

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

	        message("vision", HIG"����紫�š���˵�����ѵ������ʥ���䣬"
                             "���ܽ���\n"NOR, users());

		me->unconcious();

        	foreach(skills_name in keys(my_sk))
		{
		me->delete_skill(skills_name);
              	}
		me->delete("mark/guofu_ok"); 	 
		me->delete("mark/guofu_over"); 	
                me->delete("mark/guofu_out"); 			
		me->set("potential", me->query_potential_limit());
		me->delete_temp("sun/reborn/ask2");
		log_file("static/reborn", sprintf("%s(%s) rewash at %s .\n",
			me->name(1), me->query("id"), ctime(time())));

   } else
   {
   	  write("��������ѡ���츳��\n");
   }
   return 1;		

}
