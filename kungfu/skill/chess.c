// ����֮���������ټ��գ�kasumi
#include <ansi.h>
inherit SKILL;

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("chess", 1);
        layer = lvl / 200;
        

        if (! layer)
        {
                tell_object(me, HIM "��Ǳ����������֮������������\n" NOR);
        } else
        if ((lvl % 200) == 0)
        {
			if (me->can_improve_skill("tanqin-jifa")&& me->query_skill("tanqin-jifa", 1) <= lvl)
	            me->improve_skill("tanqin-jifa", 1500000);
                tell_object(me, HIM "�������˵�" + chinese_number(layer) +
                            "�㾳�������֮���İ��\n" NOR);
        } else
		{
			if (me->can_improve_skill("tanqin-jifa")&& me->query_skill("tanqin-jifa", 1) <= lvl)
	            me->improve_skill("tanqin-jifa", 1500000);
                tell_object(me, HIM "��Ե�" + chinese_number(layer) +
                            "�㾳�������֮���ּ�����һ���˽⡣\n" NOR);
		}
}