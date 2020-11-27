// /kungfu/skill/lonely-sword/perform/jue.c ���ܾ�ʽ��
// by smallfish
// 2002/10
 
#include <ansi.h>

int yanlian(object me);
int halt_yanlian(object me);
void remove_pending(object me);

int perform(object me)
{
    object weapon;
    int skill;    //��ߵĽ���ֵ

    if(me->is_busy())
        return notify_fail("����æ���أ�\n");

    skill = me->query_skill("lonely-sword",1);

    if (environment(me)->query("no_fight"))
		return notify_fail("����̫���ӣ��㲻�ܾ�������������\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword")
        return notify_fail("�������޽�������������¾Ž���\n");

    if (me->is_fighting())
        return notify_fail("������ս���У��޷������ܾ�ʽ��\n");

    if (! skill || skill < 20)
        return notify_fail("��Ķ��¾Ž��ȼ�����, �����������ܾ�ʽ����\n");

    if(me->query("jing") < 50)
        return notify_fail("��ľ������ã��޷������ܾ�ʽ��\n");

    if(me->query("neili") < 110)
        return notify_fail("����������ã��޷������ܾ�ʽ��\n");

    if (! me->can_improve_skill("lonely-sword"))
        return notify_fail("���ʵս���鲻�����޷���ᡸ�ܾ�ʽ����\n");

    if (skill >= (int)me->query_skill("sword",1))
	return notify_fail("��Ļ���������Ϊ���ޣ��޷���һ���������¾Ž���\n");

    message_vision("$N�������е�" + weapon->name() + "����������������䲻���з���ȴ��������ˮ����Ȼ��ɡ�\n",me);

    me->set_temp("apply/short", ({ me->name() +"��������������"}));
    me->set_temp("pending/yanlian", 1);

    me->start_busy((: yanlian :), (: halt_yanlian :));
    return 1;
}

int yanlian(object me)
{
    object weapon;
    string *all_skills;       //���м���
    int i,sword_skill = 0;    //��ߵĽ���ֵ

    if(!living(me) || 
        me->is_ghost() || 
        !objectp(weapon = me->query_temp("weapon")) ||
        weapon->query("skill_type") != "sword" ||
        me->query_skill_mapped("sword") != "lonely-sword" )
    {
        remove_pending(me);
        return 0;
    }

    if(me->query("jing") < 50 || me->query("neili") < 110)
    {
        tell_object(me,"��ͻȻ��������������ʵ���޷��ټ����������¾Ž���\n");
        message_vision("$N�������ã�����������˼��������ƣ����ȴ�ƺ������ĵá�\n",me);
        remove_pending(me);
        return 0;
    }

    all_skills = keys(me->query_skills());
    for(i=0;i<sizeof(all_skills);i++)
    { 
        if(SKILL_D(all_skills[i])->valid_enable("sword") && all_skills[i] != "lonely-sword")
        {
            if(me->query_skill(all_skills[i],1) >  sword_skill)
                sword_skill = me->query_skill(all_skills[i],1);
        }
    }
    i = me->query_int() + (me->query_skill("sword",1)/3 + random(sword_skill));
    if(i < 100) i = 50 + random(100);

    if(random(10) == 1)
        message_vision("$N�趯"+weapon->name()+"��������̣��䲻���з���ȴ��������ˮ����Ȼ��ɡ�\n",me);
    else
        tell_object(me,"���趯"+weapon->name()+"��������̣��䲻���з���ȴ��������ˮ����Ȼ��ɡ�\n");
    me->improve_skill("lonely-sword", i);

    me->add("jing",-40);
    me->add("neili",-100);
    write(MAG"��ԡ����¾Ž���������һЩ��ᣡ\n"NOR);
    return 1;
}

int halt_yanlian(object me)
{
    object weapon;
    weapon = me->query_temp("weapon");

    tell_object(me, "���������Ӳ�����ؽ���ת��Ϣ�Ľ��ƶ�ס���漴΢΢һЦ��\n");
    message("vision", me->name() +"΢΢һЦ����ָ�ᵯ���е�"+weapon->name()+"���漴�������ơ�\n",environment(me),me);

    remove_pending(me); 
    me->start_busy(1+random(3));
    return 1;
}

void remove_pending(object me)
{
    me->delete_temp("pending/yanlian");
    me->delete_temp("apply/short");
}
