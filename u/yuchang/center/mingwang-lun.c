#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name(HIB "����������" NOR ,({ "mingwang lun","lun" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",HIB"
���������ֱ�Ϊ��ݱ����������Ⱦ�����������������Ͳ�����������
���Ļƽ�֮Ѫ���죬�������ȸ����ɱ�������е������ա��º�
��ʧ���й���ɽ����ɽ��ʰ�ã�շת�������������䲻�������ڵ���
�����������������������ֵ�ͼ�״��죬�䱣���˷�����ȴ�Ѿ�����
���ڡ�\n"NOR);
                set("value", 100000);
                set("material", "gold");
                set("wield_msg", HIB"$N����һ�У�һ���⻪�Ӱ�ս��٣���ʱ�������������·���ħ����Ϊ���������ֽ����˼��ף����\n"NOR);
                set("unwield_msg","$N����һ�Σ�$n�ѻ��������ȥ��\n");
        }
        init_hammer(300);
        setup();
}
