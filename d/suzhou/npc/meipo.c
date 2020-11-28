// ����ĩ�ա�NPC: /d/suzhou/npc/meipo.c ֻ�����������
// smallfish �޸�2001.06

#include <ansi.h>
#define MARRY_RING      "/clone/misc/wedding-ring.c"
#define RING_DIR        "/data/item/ring/"

inherit NPC;

int do_marry(string);
int do_name(string);
int do_chase(object,object);
int do_ok(object,int);
int meipo_waiting(object,object,object);
int ready_marry(object,object,object);
int wait_marry(object,object,object);
int start_marry(object,object,object);
int go_lou(object,object);
int do_back(object);
int do_bai(string);
int do_right(object me, object ob);
int return_home(object);

void create()
{
	set_name("ý��", ({ "meipo","po" }) );
	set("title", HIM""NOR);
	set("gender", "Ů��" );
	set("age", 43);
	set("long","һλ�����ܸɵ���ý�š�\n");
	set("combat_exp", 100000);
	set("attitude", "friendly");
	set("inquiry", ([
		"���" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)��ȻҪ��������ý��ѽ����\n",
		"marry" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)��ȻҪ��������ý��ѽ����\n",
		"�Ǽ�" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)�Ǽǵ�ȻҪ��������ý��ѽ����\n",
		"���" : "ý����ɫһ�䣬�е���ǿ��Ц������Ҫ...���(unmarry)����...���ҿ��ǿ����ǳɻ��ѽ��\n"
      		"��������Ҫ��һ��Ҫ��Ļ����ǵ�ȥ����֪���������ˣ���\n",
		"unmarry" : "ý����ɫһ�䣬�е���ǿ��Ц������Ҫ...���(unmarry)����...���ҿ��ǿ����ǳɻ��ѽ��\n"
      		"��������Ҫ��һ��Ҫ��Ļ����ǵ�ȥ����֪���������ˣ���\n",
		"����":"ý������Ц�����������ô����£����ѵĵط��ɲ��٣�Ҫ50 gold��,�����\n"
      		"��Ҫ���Ѳ���Ǯ������Ҫ100 gold����\n",
	]) );
	set_skill("literate", 100);
	set_skill("dodge", 500);
	set_skill("unarmed", 300);
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object me;
	int i;
	me=this_object();
	i=(int)me->query("unmarried");

	::init();
	if((int)me->query("unmarried"))
	{
		me->delete("unmarried");
		me->delete("married");
		if(i>2)
		{
			me->set("couple/married",2);
			message_vision("ý��̧�ۿ��˿�$N˵���������ǰ���˲��ٴεĻ�ɣ������µĻ������涨ÿ��һ��ֻ�����\n"
				"���ν����������������ٸ����һ�λ���ɣ�����飬������Ͳ�������ˣ���\n",me);
		}
		else
			me->set("couple/married",i);
	}
	add_action("do_marry", "marry");
	add_action("do_bai","��");
	add_action("do_name","��");
}

int accept_object(object me, object ob)//��Ǯ
{
	object meipo = this_object();

	if (!ob->query("money_id"))
     	return notify_fail("ý������Ц���������������г��кȲ���ʲô���������û�ȥ�ɣ���\n");
	if(!me->query_temp("ask_money"))//�������жϽ�Ǯ�����Ƿ���Ͻ��������
   		return notify_fail("ý���Ի���ʣ��������ʲô���׸���Ǯ����\n");
  	if(meipo->query_temp("marry/money"))//�Ѿ����˽���Ǯ��
  		return notify_fail("ý��˵��������æ����һ����˵����\n");
  	if(ob->value() < 500000)
		return notify_fail("ý��������üͷ˵������Ǯ̫���˰ɣ�50 gold�������ô����£����پͲ����ˡ���\n");
	message_vision("ý�Žӹ�Ǯ��$N˵������λ"+RANK_D->query_respect(me)+"�ҿ�û׬���Ǯ��������һ�Ҫ����ϲ�á���\n"
   		"Ҫ���ˡ����а���磬�㲻���һ�������һ��ģ������һ����԰��㷢������\n"
        "���������"HIC"���� <ĳ�˵�����>��"NOR"������������μӻ��񡣡�\n",me);
	meipo->set_temp("marry/money",me->name());   //��¼����Ǯ����
    log_file( "money/MARRY", sprintf("%s(%s)��齻Ǯ in %s��\n",me->query("name"),
		me->query("id"),ctime(time()) ) );
  	return 1;
}

int do_name(string target)//�����
{
	object me,ob,dest, *all;
	int i;
	me = this_player();
	ob = this_object();
	all = users();

	if (me->is_busy())
		return notify_fail("ý��˵��������æ����ٺ���˵���ɣ���\n");
	if( ob->is_fighting()||me->is_fighting() )
		return notify_fail("ý��˵����������û���򣡡�\n");
	if( !living(ob) )
		return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");
	if((string)ob->query_temp("marry/money")!=(string)me->name())
      return notify_fail("ý���۾�б��б�㣺������û��Ǯ����\n");
	if(ob->query("marry/waiting_que"))
		return notify_fail("ý��ЦЦ˵������Ҫ�����ҵ�Сϲȵ�ǻ�û�зɻ����أ���\n");
	if( !target || target==" ")
		return notify_fail("ý�ų��һ�����д�˼����ʣ���������˭���μ���Ļ��񣿸�������(��)�����֣���\n");
	for(i=0; i<sizeof(all); i++)
	{
		if(all[i]->query("env/invisibility")) continue;
		if( target == all[i]->name() || target == all[i]->query("id") )
			dest = all[i];
	}
    if( !dest)
		return notify_fail("ý�Ÿ����㣺�����ź�����������������ڲ�����Ϸ�У���\n");
	if (dest->is_ghost())
	   	return notify_fail("ý����ϧ�صظ����㣺����������֪����Ҫ������Ѿ����ˣ�����ڰ�˳�㣡��\n");
	ob->set("marry/waiting_que",1);//��ȵ
	ob->set("marry/me_name", me->name()+"("+me->query("id")+")");//������
	message_vision(HIG"ý��һ��ϲ����д�ϼ����֣�˫��һ�ģ��Ӷ��Ⱦͷɳ�һֻСϲȵ������ϲ����\n"
		"���㶵�һ������ʧ��������ˡ�\n" NOR,me);
	call_out("do_chase", 1, ob,dest);
	return 1;
}

int do_chase(object ob,object dest)//ϲȵ�����
{
	object obj;

	if( !objectp(dest) || !environment(dest) )
	{
		call_out("do_ok",1,ob,1);//��һ��ʧ�ܵĲ�����ȥ
		return 1;
	}
	message_vision(HIY"\n�����ͻȻ�ɹ���һֻ��ϲȵ������$N��ͷ�������ŵ�һ��ϲ��ݸ�$N��\n" NOR, dest);
	obj = new(__DIR__"obj/xitie");
        obj->set_name(HIR+(string)ob->query("marry/me_name")+"�Ľ������" NOR);
	obj->move(dest);
	call_out("do_ok", 1, ob,0);
	return 1;
}

int do_ok(object ob,int flag)//ϲȵ�ͼ�ɹ�����
{
	if(flag)
		message_vision("��ϲȵ�Ӵ���������طɽ���������ý�����ԣ�ý��Ŷ��һ��˵�����ղŵ��Ǹ���û�ҵ��������������˰ɣ���\n",ob);
	else
		message_vision("ͻȻ������ϲȵ�Ӵ���ɽ���������ý�����ԣ�ý��Ц���еظ��Ż�ϲȵ��ͷ��\n"
			"˵���������ղ��Ѿ����͵��ˣ���������˭���������˾Ϳ�ʼ�������(marry <��Ķ���>)�ɣ���\n",ob);
  	ob->delete("marry/waiting_que");
	ob->delete("marry/me_name");
	return 1;
}

int do_marry(string arg) //�жϽ��
{
	object obj, me,ob,old_target;
	me = this_player();
	ob = this_object();
	if(ob->query("marry/have_couple"))
		return notify_fail("ý��һ㶣�����������ϲ����ô�ࣿ�Բ����Ұ���ͷ��һ�ԵĻ��°��꣬�ٸ����ɣ���\n");
	if ( (string)me->query("gender") == "����")
		return notify_fail("ý�ź���һ���������޸����ԣ����ʲô�飿����\n");
	if (((int)me->query("age") < 18) && (me->query("gender") == "����")
		||((int)me->query("age") < 16) && (me->query("gender") == "Ů��"))
		return notify_fail("ý��Ц������˵�������������ڻ����ᣬ�Ժ���˵�ɣ���\n");
	if (me->is_busy())
		return notify_fail("ý��˵�����������ڲ�����æ���𣿡�\n");
	if( me->is_fighting(ob) )
	{
		if( !ob->is_killing(me) )
			ob->kill_ob(me);
		return notify_fail("ý��˵�������ã��ã���������ȥ����ɻ飡��\n");
	}
	if( ob->is_fighting() )
		return notify_fail("ý��˵������û����������˵����𣡡�\n");
	if( !living(ob) )
		return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");
	if( me->is_fighting() )
		return notify_fail("ý��˵�����ٺ٣����Ȼ������������������˵�ɣ�\n");
	if( !environment() || base_name(environment()) != query("startroom"))
		return notify_fail("ý��˵�������汧Ǹ�������ں�æ��������һ�ᵽ�����������Ұɡ���\n");
	if( (string)me->query("class")=="bonze"||(string)me->query("jobname")=="bonze" )
		return notify_fail("ý��Ц��������������ô���ŷ��Ҳ�뿪ɫ������?��\n");
	if( (string)me->query("jobname")=="taoist" )
		return notify_fail("ý��ҡ��ҡͷ�����������˵������Ƿ��Ĳ�����������Ҫ�����룬���ǻ����������ɣ���\n");
	if(!arg ||!objectp(obj = present(arg, environment(me))))
		return notify_fail("ý��˵������������Ҫ������һ������ѽ����\n");
	if( me->query_temp("pending/pro"))
		return notify_fail("ý����������ף���Ļ��������ڽ������𣿻�Ҫ��ʲô����\n");
	if( obj->query_temp("pending/pro") )
		return notify_fail("ý��˵��������������˽����𣿡�\n");
	if( !obj->is_character() )
		return notify_fail("ý��˵���������ⲻ�����Լ������𡣡�\n");

	if( mapp( me->query("couple")))
	{
		if ((int)me->query("couple/married")>2)
			return notify_fail("ý�ŷ��˷���Ե����������˵����������͸���˵������ô�����ˣ�\n"
				"�����ʵ�ڲ��ܰ���ʲô�ˣ��������̫���ˣ�����͢�ټͣ��ǲ�׼�ٸ�����\n"
				"���������ˣ������Լ�ȥ����Ұԧ��ɣ�\n");
		if ( me->query("couple/have_couple") )
		{
			if ( obj == present((string)me->query("couple/couple_id"), environment(me)) )
				return notify_fail("ý������������Ǳ������Ƿ���ѽ�����ﻹҪ��������\n");
			if ((string)me->query("gender") == "Ů��")
				return notify_fail("ý��˵���������Ѿ����з�֮���ˣ����ﲻ�����ػ�ġ���\n");
			else
				return notify_fail("ý��˵���������Ѿ����и�֮���ˣ����ﲻ�����ػ�ġ���\n");
		}
	}
	if( mapp( obj->query("couple") ) )
	{
      if ((int)obj->query("couple/married")>2)
	      return notify_fail("ý�ŷ��˷���Ե����̾�˿����������������˵������ô�����ˣ���\n"
   	   "����ʵ�ڲ��ܰ�����ʲô�ˣ�����û���⣬��"+obj->name()+"������̫���ˣ�\n"
      	"����͢�ټͣ��ǲ�׼�ٰ����������ˣ�����ȥ����Ұԧ��ɣ�\n");
     	if( obj->query("couple/have_couple") )
		{
			if((string)obj->query("gender") == "Ů��")
				return notify_fail("ý��˵������ϧ���Ѿ����з�֮���ˣ����ﲻ�����ػ�ġ�\n");
			else
				return notify_fail("ý��˵������ϧ���Ѿ����и�֮���ˣ����ﲻ�����ػ�ġ�\n");
		}
	}
	if( !living(obj) )
		return notify_fail("ý��ҡҡͷ˵������"+ obj->name()+"���ڻ�û���ѹ������һ�����ȷ������˫��������Ը�ġ���\n");
	if(obj == me)
		return notify_fail("ý��˵���������ⲻ�����Լ������𣿡�\n");
	if((string)obj->query("gender") == (string)me->query("gender"))
		return notify_fail("ý�ž��������ۣ�����ͬ�������Բ��������Ӵ��������£���\n");
	if( !userp(obj) )
		return notify_fail("ý��˵�������Բ�����ֻ�ܺ���ҽ�顣��\n");
	if(ob->query_temp("marry/money")!=me->name()
   		&&ob->query_temp("marry/money")!=obj->name())   //ֻҪ������һ���˸�������
   	{
		me->set_temp("ask_money",1);
    	obj->set_temp("ask_money",1);//��ʾ�������ϣ����Ը�Ǯ����ֹ���������׸�Ǯ
   		return notify_fail("ý��Ц�����ص��������Ҫ��һ��Ǯ��ඣ�Ҫ50 gold������Ǯ���ҿ�û������죡\n");
	}
	if(!me->query_temp("marry/answer"))
	{
		message_vision(HIG"ý��̯����Ե��������߶߶��˵�����������һ���ӵ�������£��ɲ���\n"
   			"�����㣬���������������ˡ�ÿ����ֻ��������������ν��������\n"
			"���ҿ�����"HIC"  "+me->name()+"���"+(int)me->query("couple/married")+"�λ飻  "+obj->name()+"���"+(int)obj->query("couple/married")+"�λ飻    "
			HIG"�õģ�\n������������濼��һ�£��ǲ�������Ը��ͶԷ���飿��\n"NOR,me);
		obj->set_temp("marry/answer",1);
	}
	if( (object)obj->query_temp("pending/marry")!=me )
	{
		if ((string)obj->query("gender") == "Ů��")
			message_vision(MAG "\n$N����$n�ʵ�������Ը��޸����𣿡�\n\n"NOR, me,obj);
		else
			message_vision(MAG "\n$N����$n�ʵ�������Ը��Ȣ���𣿡�\n\n"NOR, me,obj);

		if( objectp(old_target = me->query_temp("pending/marry")) && old_target != obj )
			tell_object(old_target, YEL + me->name() +
                        "ȡ���˺��������ͷ��\n" NOR);
		me->set_temp("pending/marry", obj);
		if ((string)obj->query("gender") == "Ů��")
			tell_object(obj, MAG "�����Ը��޸���������Ҳ��" + me->name()
			+ "("+(string)me->query("id") + ")"+ "��һ�� marry ָ�\n" NOR);
		else
			tell_object(obj, MAG "�����Ը��Ȣ��������Ҳ��" + me->name() +
			"("+(string)me->query("id") + ")"+ "��һ�� marry "+(string)me->query("id")+" ��ָ�\n" NOR);
		write(MAG"�����㼱�����������������˵ͬ��...\n" NOR);
		return 1;
	}
	message_vision(MAG "\n$N����$n����˵������Ը�⣡\n\n"NOR, me,obj);
	message_vision(MAG "ý�źǺ�Ц�������Ǿͺã��Ǿͺã������ҵ����ߵ���Ե����׼�����ðɣ���\n"
		"˵�꣬ý��һŤһŤ���߽��˶��ߵĴ��á�\n" NOR, obj, me);
	me->delete_temp("ask_marry");//���ȡ���ʽ��Ĳ���
	obj->delete_temp("ask_marry");//���ȡ���ʽ��Ĳ���

	ob->delete_temp("marry/money");//ý��ȡ������Ǯ�Ĳ���
	ob->set("marry/have_couple",1);//ý�������ֻ�����
	ob->move("/d/suzhou/yinyuan-tang");

	me->set_temp("pending/pro",1);
	obj->set_temp("pending/pro",1);//������

	me->set("couple/couple_name",(string)obj->name());
	me->set("couple/couple_id",obj->query("id"));
	obj->set("couple/couple_name",(string)me->name());
	obj->set("couple/couple_id",me->query("id"));//��ʽ������

	if ((string)obj->query("gender") == "Ů��")
	{
		me->set("couple/couple_gender", "����");
		obj->set("couple/couple_gender", "�ɷ�");
	}
	else
	{
		obj->set("couple/couple_gender", "����");
		me->set("couple/couple_gender", "�ɷ�");
	}
	call_out("meipo_waiting", 1,ob,me,obj);
 	return 1;
}

int meipo_waiting(object ob,object me,object obj)//ý�ŵȰ���
{
	if(ob->query_temp("wait_time") == 200 )
	{
		say( "ý���ɻ��˵������С����������Ҳ�������ѵ�������Ե�޷ݣ�����������ȡ���գ�\n"
      	"������ǰ�׬��50 gold�ˣ��ǺǺ�...��\n\n");
		call_out("do_back", 0, ob);
		return 1;
	}
	if( environment(ob)==environment(me)&&environment(ob)==environment(obj) )
	{                                                 //���˶���
		ob->delete_temp("wait_time");
		call_out("ready_marry", 1,ob,me,obj);
	}
	else
	{
		if( environment(ob)==environment(me)&&environment(ob)!=environment(obj) )
		{
			if( random(10) == 0 )
			say("\ný���ʵ�����"+me->name()+"����ȥ����"+obj->name()+"��ô�����������ѵ���Ը���ˣ�\n");
			ob->add_temp("wait_time",1);               //����һ��obj����
			call_out("meipo_waiting", 1, ob,me,obj);
		}
	   	else if( environment(ob)!=environment(me)&&environment(ob)==environment(obj) )
		{                                            //����һ��me����
			if( random(10) == 0 )
			say("\ný���ʵ�����"+obj->name()+"����ȥ����"+me->name()+"��ô�����������ѵ���Ը���ˣ�\n");
			ob->add_temp("wait_time",1);
			call_out("meipo_waiting", 1, ob,me,obj);
		}
		else
		{
			ob->add_temp("wait_time",1);
			call_out("meipo_waiting", 1, ob,me,obj);
		}
	}
	return 1;
}

int ready_marry(object ob,object me,object obj)//׼������
{
	object room,npc;

	if(!( room = find_object("/d/suzhou/yinyuan-tang")) )
	room = load_object("/d/suzhou/yinyuan-tang");

	message("vision", HIY "\ný�Ÿ����е��������죬�ɻ�Ķ������ˣ����ϲ���ϲ�ã���\n" NOR, room);
	message("vision", HIC"\nֻ���ú�����һ��Ų�����ʮ����������������·���������Ů�����������ܽ�����\n"
		"ߴߴ�����������ţ��ַ�ͷ�ܿ��ˣ�ʱ��ʱ��Ц�ſ�һ��"+me->name()+"��"+obj->name()+"��\n\n"NOR, room);
	say("ý�Ŷ���λ����˵��������Ҫ�ż������Ƕ��Ǻ��о���ģ��ܿ�ͻ᲼�úõģ���\n"
		CYN"ֻ����ߵ���������ȥ��æ�ò����ˡ�\n"NOR);
	call_out("wait_marry", 1, ob,me,obj);
	return 1;
}

int wait_marry(object ob,object me,object obj) //����ϲ��
{
	object room,m_cloth,w_cloth;
	if(!( room = find_object("/d/suzhou/yinyuan-tang")) )
		room = load_object("/d/suzhou/yinyuan-tang");
	ob->add_temp("wait_time",1);
	switch(ob->query_temp("wait_time"))
	{
   	case 0:
    	say(RED"\nһ��С�һ��ܹ������е�����ý�ţ����ֽ��Ǯ�����ˣ���ý�ŸϽ�����һЩǮ��\n\n"NOR);
		break;
	case 1:
     	say(MAG"\nͻȻ���Ǳߵ�С����е�����ý�ţ���ԧ�����������������ý��һ�������ұ�����ȥ�㣡��\n\n"NOR);
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 2:
     	say(CYN"\n�ĸ��һ��Ӵ��Ӵ��̧��һֻ�����Ӵ�����������߹���ý�Ŷ�����������Щ����㣡��\n\n"NOR);
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 3:
		say("\ný��һ����ס����ܹ���һ��С���ӣ���ӭ��¥��ϲ�綩���𣿿�ȥ����\n\n"NOR);
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 4:
		say(YEL"\n�Ǳߵ��˽е��������û��������������������������\n\n"NOR);
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 5:
     	say("\n�Ǳ��ֽ���������ý�ţ�����Ǯ���ͻ����İɣ��������ˣ���ý�ŸϽ��ܹ�ȥ��\n\n");
	 	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 6:
     	say(CYN"\ný��һ·С�ܹ��������������������ģ����ͷ��ͷ�У����죬������׼��ϲװ����\n\n"NOR);
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 7:
	  	say(WHT"\nһ�������ְ˽ŵ�̧���˼��Ŵ����ӣ��������Ϲ���һ������\n"HIR
"			       ��      ��\n"
"			    ����������������\n"
"			    ����������������\n"
"			     ������  ������\n"
"			     ������  ������\n"
"			      ����    ����\n"
"			    ����������������\n"
"			     ������  ������\n"
"			     ������  ������\n\n"NOR);
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
   	case 8:
     	say(YEL"\n�������ֿ�ʼ���Ի������������������������ʶ����ʶ���ˣ��׷׹�����أ�����ϲ��ϲ����\n\n"NOR);
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 9:
  	  	say("\n����С����Ц������һ�߲������Σ�һ�߻���ҧ�Ŷ��䣬��ʱ��͵�ۿ������ˡ�\n\n");
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 10:
  	  	say("\n��λ������Ů������һ�״���߹����۵ݸ����ɣ�һ����ߴ���ˮ���佻����������������������ﴩϲװ����\n\n");
  	  	m_cloth = new("/d/suzhou/npc/obj/longpao");
  	  	w_cloth = new("/d/suzhou/npc/obj/yunxiu");
  	  	if(me->query("gender")=="����")
  	  	{
  	  		m_cloth->move(me);
  	  		w_cloth->move(obj);
  	  	}
  	  	else
  	  	{
  	  		m_cloth->move(obj);
  	  		w_cloth->move(me);
  	  	}
	  	call_out("wait_marry", 1, ob,me,obj);
		break;
	case 11:
		message("vision", HIY "\ný�Ÿ�������һ��������׼�������𣿡�����Ӧ���������ˣ���\n"
		"ý�������ϳ��������������������������ֻ��񡭡�����\n"
		HIM"��ʱ���������������ڴ��������ɰ���ӵ���������ְ˽Ÿ����ɡ����ﻻ�����£�\n"
			"׺ӵ�������������ȥ��\n"NOR, room);
		call_out("start_marry", 1, ob,me,obj);
		break;
   }
   return 1;
}

int start_marry(object ob,object me,object obj) //��ʼ����
{
	object moon,room;
	string msg;
	if(!(room = find_object("/d/suzhou/yinyuan-tang")))
		room = load_object("/d/suzhou/yinyuan-tang");
	moon=new(__DIR__"yuelao");
	moon->move(room);
	message("vision", "\n����һ�������Ц��һλ�����������ߣ��첽������У��ڳ���������Ů��������ݣ�\n"
   	"����������үү�������ϰڰ��֣�Ц�Ǻǵؿ���"+me->name()+"��"+obj->name()+"�����ͷ����\n"
      "���ã��ã��ɲ�Ůò������֮�ϣ�����֮��ѽ����\n"
   	HIY"\ný��һ���֣�ϲ���ָ���ֻ�������ϸ��������������ɡ�����ݡ���ء�������\n"NOR,room, moon);
	CHANNEL_D->do_channel(moon, "mudnews",
	   sprintf("����%s��%sϲ����Ե�����ô���ʱ��ʼ��\n",me->name(),obj->name()));
	say("ý����С���ض���������˵������˳�����롮�� ��ء��� ���úͰ� �Է������֡�����\n");
	me->set_temp("pending/bai",1);
	obj->set_temp("pending/bai",1);
	return 1;
}

int do_back(object ob)//����
{
	ob->delete_temp("wait_time");
	ob->delete_temp("marry");//ȡ��һ���йؽ��Ĳ���
	say("ý�����������ϣ���һŤһŤ����������ȥ��\n");
	ob->move("/d/suzhou/hongniang-zhuang");
	return 1;
}

int do_bai(string arg)//����
{
	object me,ob,obj;
	string act;

	me = this_player();
	ob = this_object();
	if (me->is_busy())
		return notify_fail("ý��˵�����������ڲ�����æ����æ����˵����\n");

	if( me->is_fighting(this_object()) )
	{
		if( !this_object()->is_killing(me) )
			this_object()->kill_ob(me);
		return notify_fail("ý��˵������������ĸ������£���Ҷ��䣬����ȥ����ɻ�ɣ���\n");
	}

	if( this_object()->is_fighting() )
		return notify_fail("ý��˵����û����������˵�����\n");

	if( !living(this_object()) )
		return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");

	if( me->is_fighting() )
		return notify_fail("ý��˵�������ٺ٣����Ȼ������������������˵�ɣ���\n");

	if( !environment()||base_name(environment()) != ("/d/suzhou/yinyuan-tang") )
		return notify_fail("ý��˵���������������ǵģ�������Ҫ����Ե�ò��е�ѽ����\n");

	if( !me->query_temp("pending/bai"))
		return notify_fail("ý��Ц�������������㷸ʲôɵѽ����\n");

	if( !objectp(obj = present((string)me->query("couple/couple_id"), environment(me)))
		|| !find_player(me->query("couple/couple_id")) )
	{
		message_vision("ý��ת��һ�������ȵ�˵��������ѽ����İ�����ôͻȻ���ˣ�������ô���У����ɢ̯�ɡ���\n"
			"��һƬ��ϧ������ҷ׷��볡��ϲ���ϵĶ���Ҳ��һ�ն��ա�\n",me);
		call_out("do_back",1,ob);
		return 1;
	}
	if(arg==" ���"||arg==" ����"||arg==" "+(string)me->query("couple/couple_name"))
		return notify_fail("���ݡ������Ĵ�֮�����ð�ǿո�\n");

	if(!arg ||(me->query_temp("pending/bai")==1 &&arg!="���")
		||(me->query_temp("pending/bai")==2 && arg!="����")
		||(me->query_temp("pending/bai")==3 && arg!=(string)me->query("couple/couple_name")))
		return notify_fail("ý��Ц���������Ұ�ʲôѽ��һ����أ����ݸ��ã�������İ��ˣ��ɱ��ٴ��ˣ���\n");

	if( (string)obj->query_temp("pending/act")!=arg )
	{
		if((int)me->query_temp("pending/bai")!=3)
		{
			tell_object(obj, MAG"��İ��������ź���� " + arg + " ��...\n" NOR);
			write(MAG "���������ȴ�����İ���...\n" NOR);
			me->set_temp("pending/act", arg);
		}
		else
		{
			tell_object(obj, MAG"��İ��������ź��㻥�ݣ����������֣���...\n" NOR);
			write(MAG "���������ȴ�����İ���...\n" NOR);
			me->set_temp("pending/act", me->name());
		}
		return 1;
	}
	else if((int)me->query_temp("pending/bai")==1)
	{
  		message_vision("��һ�ݡ��졭�ء�����$N��$n�������������ӯӯ����......\n",me,obj);
		me->add_temp("pending/bai",1);
		obj->add_temp("pending/bai",1);
		return 1;
	}
	else if((int)me->query_temp("pending/bai")==2)
	{
  		message_vision("�����ݡ��ߡ��á�����$N��$n��վ��������һЦ���ֻ�������......\n",me,obj);
		me->add_temp("pending/bai",1);
		obj->add_temp("pending/bai",1);
		return 1;
	}
	else if((int)me->query_temp("pending/bai")==3)
	{
  		message_vision("�����ޡ��ԡ��ݡ�����$N��$n���໥�������һ��......\n",me,obj);
		message_vision(HIY "����Ц�Ǻǵ�˵�������ã�$N��$n��������ʽ��Ϊ����! \n" NOR, obj, me);
		CHANNEL_D->do_channel(this_object(), "chat",
			sprintf( "��ϲ%s��%s��һ�����ϲ����Ե��\n        ��λ������ѣ���Я������ӭ��¥�μ����ǵĻ��磡\n", me->name(), obj->name()));

		me->add("couple/married", 1);        //������
		me->set("couple/have_couple",1);     //�����ѻ�״̬
		me->set_temp("married_party",1);     //���ϼǺţ�ϲ�����ϰ忴���ͻ�ͬ�⿪��ϯ
		obj->set_temp("married_party",1);    //���˶�������ֻ�����Բ�����
		obj->add("couple/married", 1);       //������
		obj->set("couple/have_couple",1);    //�ѻ�״̬

		me->delete_temp("pending/bai");
		obj->delete_temp("pending/bai");
		me->delete_temp("pending/act");
		obj->delete_temp("pending/act");
		me->delete_temp("pending/pro");
		obj->delete_temp("pending/pro");
     	me->delete_temp("ask_money");
		obj->delete_temp("ask_money");
                call_out("do_right",1,me,obj);
		call_out("last_marry",1,ob,me,obj);
		return 1;
	}
}

int do_right(object me, object ob)
{
        string fn;
        string fc;
        object ring;

        message("visoin", name() + "Ц�ŶԶ���˵���������������"
                "��ϲ�����ӣ���û��ʲô���ֻ���͸���"
                "���������һ�Խ���ָ�ɣ���\n\n", environment(me));

        fc = read_file(MARRY_RING);
        fc = replace_string(fc, "LONG_DESCRIPTION",
                            "����" + me->name(1) + "��" +
                            ob->name(1) + "�Ľ���ָ�������˵Ķ���֮�\n");

        // give ring to me
        fn = RING_DIR + me->query("id");
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        ring = load_object(fn);
        ring->move(me, 1);
        tell_object(me, HIY "������һ������ָ��\n" NOR);
        me->set("can_summon/" + "wedding ring", fn);

        // give ring to ob
        fn = RING_DIR + ob->query("id");
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        ring = load_object(fn);
        ring->move(ob, 1);
        tell_object(ob, HIY "������һ������ָ��\n" NOR);
        ob->set("can_summon/" + "wedding ring", fn);

        // record
        me->set("couple/witness", name());
        me->save();
        ob->set("couple/witness", name());
        ob->save();
        return 1;
}
int last_marry(object ob,object me,object obj)//���ý���
{
	object moon,room;
	if(!(room = find_object("/d/suzhou/yinyuan-tang")))
		room = load_object("/d/suzhou/yinyuan-tang");
	moon = present("yue lao", room);
	moon->move("/u/mudren/workroom");
	ob->delete_temp("wait_time");
	ob->delete_temp("marry/money");
	say("ý�ź��������η򣡿콫�����͵�ӭ��¥���л��磬�Һ����ϾͲ�ȥ�ˣ��Ǻǣ���\n˵��һŤһŤ����������ȥ��\n");
     write_file( "/log/money/MARRY", sprintf("%s(%s) and %s(%s) married in %s��\n",me->query("name"),me->query("id"),
		obj->query("name"),obj->query("id"),ctime(time()) ) );
	ob->delete("have_couple");
	ob->move("/d/suzhou/hongniang-zhuang");
	message_vision(HIR"���ɰ���ӵ����λ���ˣ������ſڵ�������컨�Σ�ֻ���η���һ������Σ���\n"
   		"һ���˴������ر���ӭ��¥......\n"NOR,me,obj);
	me->move("/d/suzhou/jiao1");
	obj->move("/d/suzhou/jiao2");
	call_out("go_lou",8,me,obj);
	return 1;
}

int go_lou(object me,object obj)
{
	object npc;
	message_vision("\n    ���˺ó�һ�����ֻ���η���һ����������������������һ�������䵽�˵��ϣ�\n"
   	"$N��$n�ӽ���������һ����ԭ���Ѿ�����ӭ��¥�������ֱ�ӵ����һֱ���˶�¥�����á�\n"
      "ֻ��һ��Ǻ�Ц����ӭ��¥�ϰ�ϲ����Ц�������ӭ����������ϲ��λ���ˣ���ϲ��ϲ����\n",me,obj);
	npc=new("/d/suzhou/npc/xi-laifu");
	npc->set("name1",me->name());
	npc->set("name2",obj->name());//˫������
	npc->move("/d/suzhou/xifu-tang");
	me->move("/d/suzhou/xifu-tang");
	obj->move("/d/suzhou/xifu-tang");
	return 1;
}

int return_home(object home)//���Ǳ�׼�̳��еĸú�������ֹ�����и��£�ý�Żؼ�
{
    if( !environment()||  environment()==home ) return 1;
	if( !living(this_object()) ||  is_fighting()) return 0;
	if( this_object()->query("marry")) return 0;//�н��Ĳ����Ͳ���ȥ

    message("vision", this_object()->name() + "����ææ���뿪�ˡ�\n",
    	environment(), this_object());
    return move(home);
}
