// ����ĩ�ա�NPC: /d/suzhou/npc/xi-laifu.c  ��ϲ����ֵ�ϲ�����ϰ�
// llm 99/07/09 �޸�2000.09

#include <ansi.h>

inherit NPC;
int ask_party();
void start_party(object,object);
int do_start();
int do_serve();
void finish_party(object,object);
int give_money(object,object);
int do_kill(string);
int do_exert();
int do_steal(string);
int kick(object);

void create()
{
	set_name("ϲ����",({"xi laifu","xi","laifu" }));
   set("title", "ӭ��¥�ϰ�");
   set("age", 42);
   set("gender", "����");
   set("attitude", "friendly");
   set("combat_exp", 50000);
   set_skill("unarmed", 100);
   set_skill("dodge", 100);
   set_skill("parry", 100);
   set("per", 20);

	set("inquiry", ([
		"name": "ϲ�����Ǻ�Ц������С�������е㸣������ϲ������������������ϰ塣\n",
		"here": "ϲ����ҡͷ���Ե�˵��������ӭ��¥���Ƿ�Բ��ʮ�����¥����ϲ�绹��Ҫ�����������\n",
		"��" : (: ask_party :),
		"ϲ��" : (: ask_party :),
		"ϯ" : (: ask_party :),
		"��ϯ" : (: ask_party :),
		"ϲ��" : (: ask_party :),
		"����" : (: ask_party :),
		"party" : (: ask_party :),
		"����":"ϲ�����Ǻ�Ц���������˵���𽻸��Һ��ˣ�����ת�������ǣ���\n",
		"��":"ϲ�����Ǻ�Ц���������˵���𽻸��Һ��ˣ�����ת�������ǣ���\n",
		]) );
   setup();
   carry_object("/d/beijing/npc/obj/hupi")->wear();
}

void init()
{
	object me=this_player();
	::init();
	if(!environment()->query("no_fight"))
		environment()->set("no_fight",1);//���˵���Ϊ����ս��
	if( interactive(me) && !is_fighting() )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, me);
	}
	add_action("do_serve", "kaixi");
	add_action("do_finish", "jieshu");
	add_action("do_start", "kaishi");
	add_action("do_kill", ({"kill","fight","hit","perform","yong","ge","touxi"}));
	add_action("do_steal", "steal");
	add_action("do_exert", ({"exert","yun"}));
}

int greeting(object me)
{
	if( !me || environment(me) != environment() ) return 0;
	if(me->query_temp("married_party") )//����
		write("ϲ�ϰ���㹰�ֵ�����ϲ�粼�õò���ˣ��ȿ���������������ϲ������ˣ���\n");
	else if(me->query_temp("kick"))//���ߵ���
		write("ϲ�����������һ���������볢���Ϸ�ķ�ɽ��Ӱ�Ⱦ���ʵ�㡣��\n");
	else if(!query_temp("party_finish"))//ϲ��δ��������ϲ�Ƶ���
		write("ϲ�ϰ���ͷ����Ӵ��������ϲ��ѽ�����˵�������Ҵ��գ������Ҿ��С���\n");
	else
		write("ϲ�ϰ�һ���֣������Ժã����ߣ���\n");
	return 1;
}

int accept_object(object me, object ob)
{
	int i;
	if(!query("name1")||!query("name2"))
		return notify_fail("ϲ�����Ի�ؿ����㣺����������û��˭��ϲ��ѽ������˭���񣿡�\n");
	if(query_temp("party_finish"))
		return notify_fail("ϲ�ϰ�Ǻ�һЦ�����������ˣ�ϲ���Ѿ������ˣ�������ֱ�Ӹ����˰ɣ���\n");
	if (!ob->query("money_id"))
     	return notify_fail("ϲ�ϰ�������üͷ���������Ͳ�ʱ���Ͷ����ˣ���ϲ�ƻ��Ǹ��ֽ�ĺã���\n");
	if(me->query_temp("married_party"))//����
		return notify_fail("ϲ�ϰ�һ㶣���Ц�������Լ����Լ�����Ҳû�������Ա��˳��ŵ��°ɣ���\n");
	i = ob->value();
	if(!me->query_temp("songli"))//��ֹ��ҷ�������ɧ��Ƶ��
	{
		CHANNEL_D->do_channel(this_object(), "chat",
			sprintf("%s����%s��%s�»��ϲ�����Ϻ���"+MONEY_D->price_str(i)+"��\n",me->name(),query("name1"),query("name2")));
		me->set_temp("songli",1);
	}
	if((int)me->query_temp("songli")>10&&i<100000)
	{
		me->add_temp("songli",-1);
		call_out("kick",0,me);
	}
	else if((int)me->query_temp("songli")>7&&i<100000)
	{
		write("ϲ�������õ������Ҿ����㰡����������͵���Ϊֹ�ɣ�����ȥ�Ҳ������ˣ���\n");
		me->add_temp("songli",1);
	}
	else if((int)me->query_temp("songli")>4&&i<100000)
	{
		write("ϲ��������Ц�����������ǲ��������ҵģ�Ҫ�����һ��ͷ�������ˣ���\n");
		me->add_temp("songli",1);
	}
    else
        me->add_temp("songli",1);
	add("money",i);//��¼�����������
	return 1;
}

int ask_party()
{
	object me,ob,wife;
	ob=this_object();
	me=this_player();
	if( me->query_temp("host_of_party"))
		message_vision("$N��$n˵��������ϲ�粻�����ڿ����𣿡�\n", ob, me);
	if( !me->query_temp("married_party") )
		message_vision("$N���˷��ʱ�����$n���ɵ��ʵ�����ý�ź���û���������������ϲ�ۣ��᲻�����ˣ���\n", ob,me);
	if( (string)me->query("gender")=="Ů��" )
		message_vision("$NЦ�Ŷ�$n˵������ý���������ɵ��������ⶩ��ϯ�����ǽ�����ɷ����ʰɣ���\n", ob,me);
	if( !objectp(wife=present(me->query("couple/couple_id"), environment(me))) )
		message_vision("$N��$n˵�������Ӷ�û������ϲ����ô����\n", ob,me);
	if( ob->query_temp("ready_to_party") )
		message_vision("$N��$n������˼��˵������������һϯ�أ�Ҫ�������������ɣ�\n",ob,me);
	if( (string)environment(ob)->query("short")!="ϲ����" )
		message_vision("$N��$nΪ�ѵ�˵�����Բ��𣬵��һص�׼������˵�ɣ���\n",ob,me);
	if( me->query_temp("ready_to_ask") )
		message_vision("$N��$n���ͷ���˵���������Ƕ�˵��������ô�ʸ�û�꣡��\n",ob,me);
	else
	{
		me->set_temp("ready_to_ask",1);//�����ʹ��˵ļǺ�
		ob->set_temp("ready_to_party",1);//�ϰ忪ʼ�Ǻ�
		me->set_temp("host_of_party",1);//���ɵļǺ�
		me->delete_temp("married_party");
		wife->delete_temp("married_party");
		message_vision("ϲ������$N���ͷ���������Ͼ��ܷԸ��������ϸ���׼������\n",me);
		call_out("start_party",1,ob,me);
	}
	return 1;
}

void start_party(object ob,object me)
{
	command("chat* "+name()+"һ���ֵ���������һ��ֵǧ�𣬾Ʋ���������������ӭ��¥���ҵ�Ϊ"+query("name1")+
		"��"+query("name2")+"\n��ϲ�磬��ӭ��λǰ��������\n\n");
	message_vision("ϲ�ϰ�ת���ֶ�$NС�����˼��䡣\n",me);
	write("��Ҫ��ʼ�������� kaishi������뿪ϯ�������� kaixi��\n"
		"��ҳԱ��ˣ������˾Ϳ��Խ�����(jieshu)��");
	me->delete_temp("ready_to_ask");
	me->set_temp("ready_to_party", 1);//����׼����ʼ�Ǻ�
}

int do_start()
{
	object me,ob,obj,*list;
	int i;
	me = this_player();
	ob = this_object();

	if( !me->query_temp("host_of_party"))
	{
		if(!me->query_temp("married_party"))
			return notify_fail(name()+"����˵�������ֲ������ˣ���ʲô������\n");
		return notify_fail(name()+"����˵��������ask xi about ϲ�磬���Ҹ������ϯ���г��򣡡�\n");
	}
	if( !ob->query_temp("ready_to_party") )
		return notify_fail(name()+"����˵������ʼʲôѽ��������û�˰���磡��\n");
	if( me->query_temp("party_start_already") )
		return notify_fail(name()+"Ц�Ǻǵض���˵�����㿴�ⲻ���Ѿ���ʼ�����\n");

	message_vision("$N��$n���ͷ˵����ϲ�ϰ壬ϲ����Կ�ʼ�ˣ���\n\n"
		"$n���̴������ţ����������ϡ���ϲ�����ơ�����\n\n",me,ob);
	me->set_temp("party_start_already", 1);//�����Ѿ���ʼ�Ǻ�
	me->delete_temp("ready_to_party");
	tell_room( environment(ob), HIY"ϲ�ϰ�����һ�ӣ����������������̴������š�����ϲ�֡�\n"NOR);

	list = all_inventory(environment(me));
	i = sizeof(list);
	while (i--)
	{
       if( obj=new(__DIR__"obj/xijiu"))
       obj->move(list[i]);
   }
   tell_room(environment(), "\n�������߳�һ��Ư���Ļ�����Ů�������ߵ�ÿ������ǰ��\n"
		"������Ů�ݸ���һ������ϲ�Ƶ���յ���߿���ȥ��\n");
   call_out("finish_party", 600, me,ob);//10���Ӻ��Զ�����
   return 1;
}

int do_serve()
{
	object ob,me,food;
	ob=this_object();
	me=this_player();

	if( !me->query_temp("host_of_party") )
		return notify_fail(name()+"б�۵�����һ�۵���������û˵��������ʲô������\n");
	if( !me->query_temp("party_start_already") )
		return notify_fail(name()+"����Ц˵������û�����ҿ�ʼ(kaishi)������ô�ÿ�ϯ����\n");

	message_vision("$N���������ţ��ϲˣ��ϲˣ�\n", me);

	tell_room(environment(me), "���������������С��ƴ�������������һ������ζ�������̰���������\n");
	if(food=new(__DIR__"obj/jiuyan"))
        food->move(environment(me));
	return 1;
}

int do_finish()
{
	object ob=this_object();
	object me=this_player();

	if( !me->query_temp("host_of_party") )
		return notify_fail(name()+"������ص�����һ�ۣ��������ģ��������²�Ҫ��˵������\n");

	if( !me->query_temp("party_start_already") )
		return notify_fail(name()+"�Ǻ�Ц������ϲ�۲����Ѿ��������𣡡�\n");
	message_vision("$N��$n˵���������˳Եö�����ʮ�ָ�лϲ�ϰ�İ��ţ���\n", me, ob);
	remove_call_out("finish_party");
	call_out("finish_party", 2, me,ob);
	return 1;
}

void finish_party(object me,object ob)
{
	int i;
	object *list,ob1,ob2;

	message_vision(HIC"\n$N����˵������СС���磬������λ��$n��ϲ��ʹ˽�������л��ҹ��٣�\n"NOR, ob,me);
	command("gongxi " + me->query("id"));

	me->set_temp("party_finish",1);
	me->delete_temp("party_start_already");
	me->delete_temp("host_of_party");
	ob->set_temp("party_finish",1);
	message("vision","\nһ�ԵĻ�����Ů��æ�����Ѿ�ϯ�ϵĲи�ʣ����ʰ�ɾ�̧��ȥ��\n",environment(me));
	if(ob1=present("jiuxi", environment(ob)))
    	destruct (ob1);
	list = all_inventory(environment(ob));
	i = sizeof(list);
	while (i--)
	{
    	ob2=new(__DIR__"obj/xitang");
    	ob2->set("name",me->name()+"��"+me->query("couple/couple_name")+"��ϲ��");
    	ob2->move(list[i]);
	}
	tell_room(environment(ob), "\nϲ�ϰ�Ը����µĻ�ư�ϲ��һ�����ط���ÿһ���ˡ�\n");
	remove_call_out("give_money");
	call_out("give_money",1,me,ob);
}

int give_money(object me,object ob)
{
	int money,v;

	environment()->delete("no_fight");
	if( !me || environment(me) != environment(ob) )
	{
   		message_vision("ϲ�ϰ�ͻȻ������һ�������ף���ȥ�����ˣ������յ���𶼲�Ҫ�ˣ���һ��\n"
			"ҡ��ͷһ����������ȥ����ơ�������ŮҲһ���߽�ȥ��ϲ����һ���ӿ������ˡ�\n",ob);
		write_file("/u/llm/jilu/marry",sprintf("%s(%s)%s",me->name(),me->query("id"),ob->query("money")));
		ob->delete_temp("ready_to_party");
		ob->move("/u/mudren/workroom");//��Ҫֱ��dest���Ա���
	   return  1;
	}
//ע������ʵ�ʹ����е���һ��յ�������ϲ����ʱ�ᳬ�����أ����ϲ��ʧ
//��˸ĳɽ��ʻ�
	message_vision("\nϲ�ϰ�Ц�Ǻǵ��ߵ�$N��ǰ��һ���֣��Աߵ�С���������һ���ʱ���ϲ�ϰ�˵����\n"
		"������С�ɴ���λ���µĿ������ϵ����һ����"+MONEY_D->price_str((int)ob->query("money"))+"\n"
		"���Ѿ��л��ת��������Ǯׯ�ʻ�������ȥ�鿴�鿴����˵��Ȼ��һ���߽����ò����ˡ�\n",me);
    me->add("balance",money);
	ob->delete_temp("ready_to_party");
  	ob->move("/u/mudren/workroom");//��Ҫֱ��dest���Ա���
	return 1;
}

int do_kill(string arg)
{
	write("ϲ����������ֱҡͷ�������ϲ�����Ӷ��ָ�ʲô������\n");
	return 1;
}

int do_exert()
{
   write("���������һ������\nϲ�����������һ�ۣ����ճԹ�������Ҫ�����ڹ�����\n");
   return 1;
}

int do_steal(string arg)
{
	object me = this_player();
	object ob = this_object();
	if(me->query_temp("steal_xiyan")<5)
	{
		message_vision("$N����֣���Ҫ͵��ʲô��\n$n��$N��������������컯��ʩ�����ԣ�\n",me,ob);
		me->add_temp("steal_xiyan",1);
		return 1;
	}
	else if(me->query_temp("steal_xiyan")<8)
	{
		message_vision("ϲ�������ö�$N���������Ҫ�������Բ��ĵĻ����ҽ����������ץ������ȥ����\n",me);
		me->add_temp("steal_xiyan",1);
		return 1;
	}
	message_vision("���������������죬ָ��$N��ϲ�������������С͵�𣿡�ϲ�ϰ�������������ǣ���\n"
	"���ǲ�����һӵ���ϣ���$N�������˳�ȥ��\n",me);
	tell_object(me,"�㻹û�������ʲô�£��ͱ�һȺ�������ų���ӭ��¥......\n");
	me->set("jianyu/what","steal");//����ԭ��
	me->set("jianyu/where","suzhou");//�����ص�
	me->apply_condition("jianyu",20);//����ʱ��
	me->move("/d/wuguan/jianlao_yz");//������
	return 1;
}

int kick(object me)
{
	if( !me || environment(me) != environment() ) return 0;
	message_vision("ϲ�ϰ�ŭ��һ�������������㻹���������ţ���˵�꣬ϲ����һ̧�ȣ�$N��ʧɫ��\n"
		"ȴ��ôҲ�޷���ù���һ�š����̣�����һ�������ӴӴ�������˳�ȥ��\n"
		"ϲ�ϸ��������ϳ������Ǻ�Ц������û���ˣ����������������\n",me);
	tell_room("/d/suzhou/xiaozheng","ͻȻһ����Ӱ�����ߵ�ӭ��¥��¥�ɳ��������������ˤ�ڵ��ϣ�ϸ��ȴ��һ�����ˤ�����ˡ�\n");
	me->set_temp("kick",1);
	me->move("/d/suzhou/baodaiqiao");//�Ƶ�¥�µĴ�ַ����Ｔ��
	tell_object(me,"��ֻ��ƨ��һ��ʹ�������ѷ���������������ڵ��ϣ�������������ƺ�ȫ�������ˡ���\n");
	if(me->query("qi")>30) me->add("qi",-30);
	else me->unconcious();
}
