#include <ansi.h>; 
#include <command.h>; 
inherit ITEM; 
void create()
{
        set_name(WHT "�������澭����ƪ" NOR, ({ "zhenjing canpian", "canpian", "zhenjing", "jing"}));
        set_weight(500);
        if (clonep())
                     set_default_object(__FILE__); 
        else {
                set("unit", "��");
                set("material", "paper");
                set("no_sell", 1);
                set("long", WHT "\n����һ���ñ�ֽд�ɵ��飬��Ƥ��д�С������澭����\n"
                            "�����֡���Ƥ���ƣ������Ѿ�����ܾ��ˡ��澭�м���\n"
                            "�д����ơ������׹�צ�������޷��Ⱦ��������������\n"
                            "����(read)����\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book;
        int lv;

        if (! arg)
        {
                write("�ж������澭ָ���ʽ��read <����> from <�����澭>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("�ж������澭ָ���ʽ��read <����> from <�����澭>\n");
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

        if (where->query("no_fight")
           && me->query("doing") != "scheme")
        {
                write("���޷������ﾲ�������ж��澭��\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if (! id(book))
        {
                write("����û���Ȿ�顣\n");
                return 1;
        }

        if ( skill != "������צ"
           && skill != "��������צ")
        {
                write("�澭�ϲ�û�м���������о������ݡ�\n" NOR);
                return 1;
        }

        if (me->query_skill("sanscrit", 1) < 200)
        {
                write("�������ˮƽ̫�ͣ��޷������澭�������ص����ݡ�\n");        
                return 1;
        }

        if ((int)me->query("combat_exp") < 800000)
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if ((int)me->query("jing") < 100
           || (int)me->query("qi") < 100
           || (int)me->query("neili") < 200)
        {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }

        if (skill == "������צ")
        {
                if (me->query("can_perform/jinyin-baiguzhao/zhua"))
                {
                        write("�㲻���Ѿ�������\n"); 
                        return 1;
                }
                if (me->query_skill("jinyin-baiguzhao", 1) < 120)
                {
                        write("������׹�צ�����������޷�������С�\n");
                        return 1;
                }

                tell_object(me, HIG "��ѧ���ˡ�������צ����\n" NOR);
                me->receive_damage("jing", 80);
                me->start_busy(2);
                me->set("can_perform/jinyin-baiguzhao/zhua", 1);

           	if (me->can_improve_skill("claw"))
                   	me->improve_skill("claw", 1500000);
           	if (me->can_improve_skill("jinyin-baiguzhao"))
                   	me->improve_skill("jinyin-baiguzhao", 1500000); 
           	if (me->can_improve_skill("martial-cognize"))
                   	me->improve_skill("martial-cognize", 1500000);

                return 1; 
        }

        else

        if (skill == "��������צ")
        {
                if (me->query("can_perform/jinyin-baiguzhao/duo"))
                {
                        write("�㲻���Ѿ�������\n"); 
                        return 1;
                }
                if (me->query_skill("jinyin-baiguzhao", 1) < 140)
                {
                        write("������׹�צ�����������޷�������С�\n");
                        return 1;
                }

                tell_object(me, HIG "��ѧ���ˡ���������צ����\n" NOR);
                me->receive_damage("jing", 80);
                me->start_busy(2);
                me->set("can_perform/jinyin-baiguzhao/duo", 1);

           	if (me->can_improve_skill("claw"))
                   	me->improve_skill("claw", 1500000);
           	if (me->can_improve_skill("jinyin-baiguzhao"))
                   	me->improve_skill("jinyin-baiguzhao", 1500000); 
           	if (me->can_improve_skill("martial-cognize"))
                   	me->improve_skill("martial-cognize", 1500000);

                return 1; 
        }

        else
        
        if (skill == "jiuyin-baiguzhao" || skill == "�����׹�צ")
                skill = "jiuyin-baiguzhao";

        if (! SKILL_D(skill)->valid_learn(me))
               	return 0;

        if (! me->can_improve_skill(skill))
       	{
               	write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
               	return 1;
       	}

        lv = me->query_skill(skill, 1);

        if (lv >= 180)
	{
                write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˡ�\n");
                return 1;
        }

        // �츳��ӱ�����ж��ٶ�
        if (me->query("special_skill/clever"))
                me->improve_skill(skill, me->query("int") + 5);
        else
                me->improve_skill(skill, me->query("int") + 1);

        me->receive_damage("qi", random(50) + 30);
        me->receive_damage("jing", random(50) + 30);
        me->add("neili", -lv);
        message("vision", me->name() + "��ר�ĵ��ж������澭��\n",
                          environment(me), me);
        write("����ϸ�ж������澭�������ĵá�\n");
        return 1;
}
