// shuanger.c
#include <ansi.h>
inherit F_DEALER;
inherit NPC;
// inherit F_UNIQUE;

int ask_go();

void create()
{
	set_name("˫��", ({ "shuang er", "shuang","er"}));
	set("title", HIW "������˫" NOR);
	set("nickname", HIM "�󹦸��" NOR);
	set("gender", "Ů��");
	set("age", 15);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 15);
	set("int", 25);
	set("con", 25);
	set("dex", 30);
	
	set("max_qi", 500);
	set("max_jing", 200);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 50);
	set("combat_exp", 50000+random(10000));
	set("score", 20000);

	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set_skill("sword", 80);
	set_skill("huashan-xinfa", 70);
	set_skill("huashan-quanfa", 70);
	set_skill("huashan-sword", 70);
	set_skill("feiyan-huixiang",80);
	map_skill("force", "huashan-xinfa");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("parry", "huashan-quanfa");
	map_skill("sword", "huashan-sword");
	map_skill("unarmed", "huashan-quanfa");

	set_temp("apply/attack", 15);
	set_temp("apply/attack", 15);
	set_temp("apply/damage", 15);
	set("inquiry", ([
	     "��Ը��Ը�������" : (: ask_go :),
	]));
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth")->wear();

	set("vendor_goods", ({         
		"/u/xiner/obj/rope",
//		"/u/xiner/obj/bojuan",
		"/u/xiner/obj/fojing",
//		"/u/xiner/obj/jianpu",
		"/u/xiner/obj/perwan",
		"/u/xiner/obj/hx_book",	//��������
		"/u/xiner/obj/feature",	//��ȸ����
		"/clone/fam/pill/xieqi",
		"/clone/fam/pill/zhengqi",
		"/clone/book/mengzi",	//����
		"/d/death/obj/tianjing",  //����쾧
		"/clone/fam/item/bless_water", // Ǭ��ʥˮ
		"/clone/fam/etc/hanjing",// ��֮��������
		"/clone/fam/etc/mozhixin",// ħ֮�ġ�ħ
		"/clone/fam/etc/huojingling",// ��֮���顤��
		"/clone/fam/etc/leishentong",// ����֮ͫ����
//		"/clone/fam/max/zhenyu",// ����������
//		"/clone/fam/max/longjia",// �������׵�
//		"/clone/fam/max/xuanhuang",// �������䵤
		"/clone/fam/pill/dimai",// ����ѪȪ
		"/clone/fam/pill/yulu",// ������¶
		"/clone/fam/pill/lingzhi4",// ǧ����֥��
		"/clone/fam/max/tianshu1",// ��������
		"/clone/book/wuji2.c",
		"/clone/tattoo/spc1",
		"/clone/tattoo/spc2",
		"/clone/tattoo/spc3",
		"/clone/tattoo/spc4",
		"/clone/tattoo/spc5",
		"/clone/tattoo/spc6",
		"/clone/tattoo/spc7",
		"/clone/tattoo/spc8",
		"/clone/tattoo/spc9",
		"/clone/tattoo/spc10",
		"/clone/tattoo/zs_spc1",
		"/clone/tattoo/zs_spc2",
		"/clone/tattoo/zs_spc3",
		"/clone/tattoo/zs_spc4",
		"/clone/tattoo/zs_spc5",
		"/clone/tattoo/zs_spc6",
		"/clone/tattoo/zs_spc7",
        }));
}

void init()
{
	object me = this_player();
	::init();
	if ( me->query("id") == "xiner" )        
	{
		add_action("do_list", "list");
		add_action("do_buy", "buy");
	}        
}
int ask_go()
{
	object me;
	string new_name,new_id,host_id;
	me=this_player();
	if(query("id")!="shuang er")
	{
		sscanf(query("id"),"%s's shuang er",host_id);
		if(query("id")==host_id)
		{
			say(query("name")+"�����۾����˿�"+
				me->query("name")+"��˵:��ȻԸ����,�Ҷ�����ġ�\n");
			return 1;
		}
		if(me->query("id")!=host_id)
		{
			say(query("name")+"�����۾����˿�"+
				me->query("name")+"��˵:���е�,�ҵ��������˵ġ�\n");
			return 1;
           	}
	}
	if ((int)this_player()->query("weiwang")>=70)
	{
		write( HIY "˫����:���˴��Ҷ�����ɽ,���˶���ׯ�����д����\n" NOR);
		write( HIY "����Ҫ�ҷ�������,��һ�����ġ�\n" NOR);
		command("nod");	
		set_leader(me);
		new_name = me->query("name")+"��Ѿ��˫��";
		new_id=me->query("id")+"'s shuang er";
		set("name",new_name);
		set("id",new_id);
		set("long","����"+new_name+"��\n"
		"����һ��ʮ���������Ů,��Լʮ���������;\n"
		"һ��ѩ�׵�����,ü����С,Ц���绨,��Ц�����ؿ����㡣\n");
	}
	else say(query("name")+"�����۾�����"+
		me->query("name")+"��˵:���е�,����û��ͬ�⡣\n");
	return 1;
}