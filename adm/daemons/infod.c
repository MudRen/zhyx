// eventd.c

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

string* info = ({	
        "��ӭ�����׻�Ӣ��ʷ����Ϸ��ҳ��http://yhhero.vicp.net ��",
        "����ZMUD�е�[����]�йر�[��Ӧָ����]���á�",
        "������Ϸǰ�����Ķ������ļ�(help)���������ѯ�����ֵ�ʦ(who -v)��",        
        "��ʹ��ָ�� show �鿴����ǰ����λ�õĵ�ͼ����ͼ�к�ɫ��˸����Ϊ�����ھ���λ�á�",
        "��Ҫ�˽Ȿ��Ϸ����ɫ����ʹ�� help feature �鿴��",
        "����Ϸ�ṩ��ʮ������ɽӽ�ǧ������ѧ�����ѡ����ѧ���ܿɲμ� help skills ��",
        "������ϵͳ���ڲ��Ժ����Ƶ��У����о��������ṩ���� ����",
});	

void create()
{
        string event;
        object eob;

        seteuid(ROOT_UID);
        set("channel_id", "��������");
        CHANNEL_D->do_channel(this_object(), "sys", "����ϵͳ�Ѿ�������");
}

int get_info_size()
{
	return sizeof(info);
}

string get_info(int i)
{
	if (i < 0 || i >= sizeof(info))
	      return "�������������������ʦ���������bug�����������ԡ�";

	return info[i];
}