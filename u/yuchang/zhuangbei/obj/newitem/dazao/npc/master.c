//dazao.c
//by wsw 2004 2 25
//����װ��
/*
dazao
     /armor		ԭʼװ��
           /file  �ļ�
           /att   ����	
     /baoshi  	����
     /time    	�����ʱ��
     /gold
     	   /num  ����
     	   /done ok	
     /done		��������
     /ask       �ʹ��ˡ�

*/

// #include <norumor.c>

#include <ansi.h>
inherit NPC;
//int do_give(string arg);
int accept_ok(object who);
int dazao();
object get_item(object who);
int do_cancel();

int do_counter();
void if_dazao(string arg,object me);
void get_room(string arg,object me);
void make_counter(string arg,object me,string str,int price);


void create()
{
       set_name(HIM"����ʦ"NOR, ({"master"}));
	   set("long","�����԰������߼��ķ��ߡ�\n");
       set("gender", "����");
        set("combat_exp", 1000);
       set("age", 26);
       set("per", 14);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 10);
       set("max_price",20);
       set("inquiry", ([
                "����" : (: dazao :),
                "dazao" : (: dazao :),
                "����" : (: do_cancel :),
                "cancel" : (: do_cancel :),
                "��̨" : (: do_counter :),
                
        ]) );//        if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
       setup();

//       carry_object("/d/obj/cloth/linen")->wear();
//	   carry_object("/d/wiz/npc/caishen")->wear();
//       add_money("silver", 1);
}

void init()
{
        int i;
        object ob;
	object *obj= all_inventory();
	
       //::init();
	if (obj) {
	    for	(i=0;i<sizeof(obj);i++) {
	    	destruct(obj[i]);
	    }
	}
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
 
 //       add_action("do_give", "give");
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
            say( name()+"Ц�����˵������λ" +RANK_D->query_respect(ob)
                                + "����������װ���İɣ���\n");
}

int accept_object(object who, object ob)
{

	int gold=F_VENDOR_SALE->get_inflation();
	string *file=({
		NEWITEMS_DIR+"/newarmor/armor",
		NEWITEMS_DIR+"/newarmor/boots",
		NEWITEMS_DIR+"/newarmor/cloth",
		NEWITEMS_DIR+"/newarmor/finger",
		NEWITEMS_DIR+"/newarmor/hands",
		NEWITEMS_DIR+"/newarmor/head",
		NEWITEMS_DIR+"/newarmor/neck",
		NEWITEMS_DIR+"/newarmor/shield",
		NEWITEMS_DIR+"/newarmor/surcoat",
		NEWITEMS_DIR+"/newarmor/waist",
		NEWITEMS_DIR+"/newarmor/wrists"});
	
	if (!who->query("dazao/ask")) {
		tell_object(who,HIW"�����Ǹ�ʲô�������л����ҿɲ�����һ��!\n"NOR);
		command("kick "+who->query("id"));
		return 0;
	} 
	if (ob->query("armor_prop/armor")) {
		if ( who->query("dazao/armor")) {
			tell_object(who,HIW"���Ѿ�������!\n"NOR);
			return 0;
		}
		if (ob->query("level") < 1) {
			who->set("dazao/armor/file",file[random(sizeof(file))]);


		}	
		else {
			who->set("dazao/armor/file",base_name(ob));
			who->set("dazao/armor/att",ob->query_entire_dbase());
		}
		gold=(ob->query("level")+1)*500*gold;
		who->set("dazao/gold/num",gold);		
		tell_object(who,HIW"��������װ����Ҫ"+
		    F_VENDOR_SALE->price_string(gold)+"�ֹ��ѡ�\n");		
		accept_ok(who);
		return 1;
	}
	//����������װ���ĵȼ���
	if (ob->query("material") == "metal" && ob->query("level") >0) {
		if ( !who->query("dazao/armor")) {
			tell_object(who,HIW"��Ҫ����ʲôװ������\n"NOR);
			return 0;
		}
		if (ob->query("level")-who->query("dazao/armor/att/level") != 1 ) {
			tell_object(who,HIW"�������������װ������ʲô���á�\n"	NOR);
			return 0;
		}
		if (who->query("dazao/baoshi")) {
			tell_object(who,HIW"���Ѿ�������!\n"NOR);
			return 0;			
		}
		who->set("dazao/baoshi/file",base_name(ob));
		who->set("dazao/baoshi/att",ob->query_entire_dbase());
		accept_ok(who);
		return 1;
	}
	//��ʯ����װ��������
	if (ob->query("material") == "baoshi" && ob->query("level") >0) {
		if ( !who->query("dazao/armor")) {
			tell_object(who,HIW"��Ҫ����ʲôװ������\n"NOR);
			return 0;
		}
		if (who->query("dazao/armor/att/level") != ob->query("level")) {
			tell_object(who,HIW"�������������װ������ʲô���ðɣ�\n"	NOR);
			command("? "+who->query("id"));
			return 0;
		}
		if (who->query("dazao/baoshi")) {
			tell_object(who,HIW"���Ѿ�������!\n"NOR);
			return 0;			
		}
		who->set("dazao/baoshi/file",base_name(ob));
		who->set("dazao/baoshi/att",ob->query_entire_dbase());
		accept_ok(who);
		return 1;
	}	
	
	//�����Ǯ��
	if (ob->query("money_id")) {
		if ( !who->query("dazao/armor")) {
			tell_object(who,HIW"���Ǯ���Ҹ��\n"NOR);
			return 0;
		}
		if ( who->query("dazao/gold/done") == "ok") {
			tell_object(who,HIW"���Ǯ�ǲ�̫���ˣ��ȼ�һ�����˰ɣ�\n"NOR);
			return 0;
		}
		if (ob->value()<who->query("dazao/gold/num")) {
			tell_object(who,HIW"̫���˰ɣ�\n"NOR);
			return 0;
		}
		who->set("dazao/gold/done","ok");
		accept_ok(who);
		return 1;		
	}
	
	tell_object(who,HIW"��������������û���ð���\n");
	command("kick "+who->query("id"));
	return 0;

}

int accept_ok(object who)
{
	who->set("dazao/time",time());
	if (who->query("dazao/armor") 
	  && who->query("dazao/baoshi")
	  && who->query("dazao/gold/done") == "ok")
	{
		who->set("dazao/done","ok");
		write("�õģ���һ��Сʱ�����ð�!\n");	
	}
	return 1;
}


int dazao()
{
	object ob,obj=this_object();
	object who=this_player();
	
	if (who->query("dazao/done") == "ok") //��װ��
	{
		if(time()-who->query("dazao/time") <= 3600) {
			tell_object(who,HIW"��Ҫ�������װ����û�д���ء�\n"NOR);
			return 1;
		}
		ob=get_item(who);
		if(ob && ob->move(who)) {
			tell_object(who,HIW"����������װ����\n");
			command("addoil "+who->query("id"));
		} else {
			tell_object(who,HIW"������˼����Ķ���Ū���ˡ�\n");
		}
		who->delete("dazao");
		return 1;
	}
	else {
		if (who->query("dazao/ask")) {
			tell_object(who,HIW"�㷳����������\n"NOR);
			return 1;
		}
		tell_object(who,HIW"����Ҫ����װ�������Ҷ����ˣ�\n"NOR);
		command(":D "+who->query("id"));
		who->set("dazao/ask","done");
		return 1;
		
	}
	
}

object get_item(object who)
{
    object ob;
    mapping attribute;
    string *key;
    int level,i,j,color;
    string *str=({
	HIW"��ͨ",
	HIW"����",
	HIW"׿Խ",
	HIW"�Ƿ�",
	HIW"��ʥ",
	});
    mixed *att=({
    	({"red",	"dodge",	({4,9,18,28,30})}),
    	({"blue",	"armor",	({13,17,46,70,75})}),
    	({"yellow",	"spells",	({4,9,18,28,30})}),	
    	({"purple",	"armor_vs_force",({80,220,410,650,700})}),
    	({"green",	"armor_vs_spells",({80,220,410,650,700})}),
    	});
    
    ob=new(who->query("dazao/armor/file"));
    if (!ob) return 0;
    attribute=who->query("dazao/armor/att");
    if (mapp(attribute)) {
 	    key=keys(attribute);
   	    key = sort_array(key, 0);
	    for(j=0; j<sizeof(key); j++) {
        	ob->set(key[j], attribute[key[j]]); 
	    }        	
    }  
    //������Ǵ������װ�������ԭ������
    if (!ob->query("changed")) { 
    	ob->delete("armor_prop");  
    	ob->set("armor_prop/armor",10);
    }        
    
    level = who->query("dazao/baoshi/att/level");
    if (level > 5) level = 5;
    if (level < 1) level = 1;
    
    //����Ǽӽ�������
    if (who->query("dazao/baoshi/att/material") == "metal") {
    	ob->set("level",level);
    	ob->set_name(str[level-1]+"��"+ob->query("name")+NOR,ob->parse_command_id_list()); 
    	ob->set("type","dazao");
    	ob->set("long",ob->query("name"));
		if (level==1) 	ob->set("armor_wiel/exp",50);
		if (level==2) 	ob->set("armor_wiel/exp",100);
		if (level==3) 	ob->set("armor_wiel/exp",500);
		if (level==4) 	ob->set("armor_wiel/exp",1000);
		if (level==5) 	ob->set("armor_wiel/exp",1500);
		
    }
    
    //����Ǳ�ʯ����
    if (who->query("dazao/baoshi/att/material") == "baoshi") {
    	j=10;
    	switch (color=who->query("dazao/baoshi/att/color")) {
    		case 1 : j=0;break;
     		case 2 : j=1;break;
    		case 4 : j=2;break;
     		case 3 : j=3;break;
     		case 6 : j=4;break;
     		case 5: j=random(sizeof(att));break;
     		case 7: j=random(sizeof(att));break;     
//     		default	j=10;	
   		}
		if (j== 10) return 0;
		ob->set("armor_prop/"+att[j][1],att[j][2][level-1]);
		//��ʯ�ټ�һ�Ρ�
		if (color == 7) {
			i=j;
			while (j == i) j = random(sizeof(att));
			ob->set("armor_prop/"+att[j][1],att[j][2][level-1]);
		}
    }
	ob->set("changed",1);
//	ob->set("long",ob->query("name"));
    return ob;	
	
}

int do_cancel()
{
	object who=this_player();
    if (who->query("dazao")) {
	who->delete("dazao");
	tell_object(who,HIW"��Ҫ�����ˣ��ðɣ���������ǰ���ҵĶ����ҿɲ���Ŷ��\n");	
	command("shrug "+who->query("id"));
    	return 1;
    } else return 0;
}

int do_counter()
{
	object me=this_player();
	
	if (me->query("playercity/counter/num") >= 1) {
		write("���Ѿ�����һ����̨�ˡ�\n");
		return 1;
	}		
	write("����Ҫ���̨���������ͻ�����Ŷ��(Y/N):");
	input_to((:if_dazao:),me);
	return 1;	
}

void if_dazao(string arg,object me)
{
	if (arg != "Y" && arg != "y") {
		write("�Ժ�û�²�Ҫ�����ң�\n");
		return;
	}
	
	write("��������Ҫ�ڷŹ�̨�ķ���ţ���ʽ��x*y*z*����");
	input_to((: get_room :),me);
}

void get_room(string arg,object me)
{
	int price;
	
	if (!arg) return;
	if(member_array(arg+".c",get_dir(PLAYERCITY_FILE_DIR)) <= -1) {
		write("û��������䡣\n");
		return ;	
	}
	
	arg=PLAYERCITY_FILE_DIR+arg+".c";
	
	if ( arg->query("owner_id") != me->query("id")) {
		write("�ⲻ����ķ��䡣\n");
		return;
	}
	if ( arg->query("outdoors")) {
		write("��̨���ܰ������⡣\n");
		return;
	}
	
	price = F_VENDOR_SALE->get_inflation();
    price *=10000;
	write("һ����̨��Ҫ����"+F_VENDOR_SALE->price_string(price)+"��\n��ȷ��Ҫ����(Y/N):");
	input_to((: make_counter :),me,arg,price);
}

void make_counter(string arg,object me,string str,int price)
{
	string counter_name;
	if (arg != "Y" && arg != "y") {
		write ("�ðɣ���Ҫ��ʱ�������ҡ�\n");
		return;
	}
	if (price > me->query("balance")) {
		write("�����л�ͷ��û����ô��Ǯ��\n");
		return;
	}
	write("�ļ�����"+str+"\n");
	//���ɹ�̨�ļ�
	counter_name=PLAYERCITY_FILE_DIR+"obj/counter-"+me->query("id")+".c";
    if (cp(PLAYERCITY_FILE_DIR+"obj/counter.c",counter_name)) {
    	write("�㻨��"+F_VENDOR_SALE->price_string(price)+"������һ����̨��\n");
    	log_file("playercity",sprintf("[%s] %s buy %s at %s.\n",ctime(time()),
    		this_player()->query("id"),counter_name,str));
    }
    else { write("���̨ʧ�ܣ�\n");return;}
    
}