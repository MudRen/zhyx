// �޺���ħ�� luohan-fumogong.c
// Editd By Vin On 29/5/2002

#include <ansi.h>
inherit FORCE;

int valid_force(string force)
{
   if ( force == "taixuan-gong")  return 0;
      else return 1;
}

int query_neili_improve(object me)
{
        int lvl;
        string fam;

        fam = me->query("family/family_name");
        lvl = (int)me->query_skill("luohan-fumogong", 1);

        // �ȹ������̻�Ʋ�������Ϊ������ת��
        if (me->query("skybook/item/xuanbingjiu")
           && fam == "������"
           && me->query("class") == "bonze"
		   && me->query("reborn"))
                return lvl * lvl * 15 * 20 / 100 / 200;
		else
		//�ȹ������̻�Ʋ�������Ϊ����ûת��
		if (me->query("skybook/item/xuanbingjiu")
           && fam == "������"
           && me->query("class") == "bonze")
                return lvl * lvl * 15 * 15 / 100 / 200;
        else
		// û�ȹ������̻�Ƶ�����Ϊ���� �Ѿ�ת��
		 if (me->query("class") == "bonze"
           && fam == "������"
		   && me->query("reborn"))
                return lvl * lvl * 15 * 14 / 100 / 200;
		else
        // û�ȹ������̻�Ƶ�����Ϊ���� û��ת��
        if (me->query("class") == "bonze"
           && fam == "������")
                return lvl * lvl * 15 * 12 / 100 / 200;
        else

        // �ȹ������̻������������� �Ѿ�ת��
        if (me->query("skybook/item/xuanbingjiu")
			&& me->query("reborn"))
                return lvl * lvl * 15 * 18 / 100 / 200;
		else
		// �ȹ������̻������������� û��ת��
		if (me->query("skybook/item/xuanbingjiu"))
                return lvl * lvl * 15 * 12 / 100 / 200;
        else
        // ��ͨ���
                return lvl * lvl * 15 * 8 / 100 / 200;
}

int valid_enable(string usage)
{ 
        return usage == "force";       
}

int valid_learn(object me)
{
        if (me->query("character") == "�ĺ�����")
                return notify_fail("�����а������˹�һ������Ҳ�ޣ��ο����ѧ������\n");

        if (me->query("character") == "���ռ�թ")
                return notify_fail("�����а������˹�ƽ�����棬�ο�Ϊ��������˼��\n");

        if ((int)me->query("int") < 30)
                return notify_fail("���������Բ��㣬��������޺���ħ�񹦡�\n");

        if ((int)me->query("con") < 30)
                return notify_fail("����������������޷������޺���ħ�񹦡�\n");

        if ( me->query("gender") == "����" && me->query_skill("luohan-fumogong", 1) > 29)
                return notify_fail("���޸����ԣ�����������������������޺���ħ�񹦡�\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ�����㣬����ѧ�޺���ħ�񹦡�\n");

        if ((int)me->query("max_neili", 1) < 1000)
                return notify_fail("���������Ϊ���㣬����ѧ�޺���ħ�񹦡�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�޺���ħ��ֻ����ѧ(learn)�������������ȡ�\n");
}

/*
int difficult_level(object me)
{
        string fam;
    
        me = this_player();

        fam = me->query("family/family_name");

        if (me->query("skybook/item/xuanbingjiu")
           && fam == "������"
           && me->query("class") == "bonze")
                return 200;
        else

        if (me->query("class") == "bonze"
           && fam == "������")
                return 300;
        else

        if (me->query("skybook/item/xuanbingjiu"))
                return 300;
        else
                return 400;
}
*/

string exert_function_file(string action)
{
        return __DIR__"luohan-fumogong/" + action;
}