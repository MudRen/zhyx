// kuihua.c ��������
// Jay 4/5/96

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

void create()
{
        set_name("��������", ({ "kuihua baodian", "baodian", "book"}));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "��������ֵ�һ�ؼ����������䡷���ഫ��һλ����̫��������\n");
                set("value", 1);
                set("material", "paper");
                set("no_sell", 1);
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int plvl; 
	int neili_lost;

	if (! arg || !id(arg))
		return 0;

        if (where->query("pigging"))
	{
                write("�㻹��ר�Ĺ���ɣ�\n");
                return 1;
        }

        if (me->is_busy())
	{
                write("��������æ���ء�\n");
                return 1;
        }

        if (me->is_fighting())
	{
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

	if (where->query("no_fight"))
	{
		write("���޷������ﾲ�������ж����䡣\n");
		return 1;
	}

        if ((string)me->query("gender") == "Ů��")
	{
                write("�Թ�û����˵Ů�˿��Զ����������䡷�ġ�\n");
                return 1;
        }

        if ((string)me->query("gender") == "����")
	{
               write("���������䡷�ĵ�һҳд�ţ������񹦣������Թ���\n");
               return 1;
        }

        if (! me->query_skill("literate", 1))
	{
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

	if (me->query_skill("pixie-jian", 1) >= 180)
	{
		write("�Ȿ�����Ѿ��о��ò���ˣ�ûʲô�ö����ˡ�\n");
		return 1;
	}

        switch(random(3))
	{
        case 0:
        	message("vision", me->name() + "͵͵��������һ�����ڶ���\n", environment(me), me);
              	break;
        case 1:
        	message("vision", me->name() + "�߶����ɧ��Ū�ˣ�������ģ��Ů�ˡ�\n", environment(me), me);
                break;
        case 2:
        	message("vision", me->name() + "�߶���߰�����Ť��Ťȥ��\n", environment(me), me);
              	break;
        }
        if ((int)me->query("jing") < 30)
	{
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }

	plvl = me->query_skill("pixie-jian", 1);
        if (plvl > 150) neili_lost = 50; else
        if (plvl > 120) neili_lost = 25; else
        if (plvl > 100) neili_lost = 15; else
	if (plvl > 60)  neili_lost = 10;
	            else neili_lost = 5;

        if ((int)me->query("neili") < neili_lost)
	{
		write("�������������޷�������ô������书��\n");
                return 1;
        }

        if (! me->can_improve_skill("pixie-jian", 1))
	{
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if (plvl > 199)
	{
                write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                return 1;
        }

        me->receive_damage("jing", random(15) + 15);
	me->add("neili", -neili_lost);
	me->improve_skill("pixie-jian", random((int) me->query_skill("literate", 1) / 3) + plvl / 5 + 1);
        write("���ж����������䡷�������ĵá�\n");
	me->stary_busy(random(3));
        return 1;
}

