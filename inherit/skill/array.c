/**************************
 * array.c
 *
 * �󷨻��������
 * #define SKI_ZHEN
 * by Find.
 **************************/

#include <origin.h>
#include <ansi.h>

inherit F_CLEAN_UP;

nosave  string mp,      // ����������
	name,		// ������
	ski_name,	// ���󷨵� id
	su_msg,		// ����ѶϢ
	skill_type;	// �����õ��书

nosave  int num,                // ��Ҫ�����Ա����
	master_level,		// �����󷨵ȼ�
	member_level,		// ��Ա�󷨵ȼ�
	master_skill_level,	// �����书�ȼ�
	member_skill_level,	// ��Ա�书�ȼ�
	e_level;		// �󷨵���Чֵ

void create()
{
	string str;
	int n = strsrch(str = base_name(this_object()),'/',-1);

	ski_name = str[n+1..];
	seteuid(getuid());
}

void skill_improved(object me) {}

string query_array_id() { return ski_name; }

int valid_learn(object me)
{
	if(!me)
		return 0;

	if( stringp(mp)
	&& !wizardp(me)
	&& (me->query("family/family_name") != mp) )
		return notify_fail("�㲻��ѧϰ����󷨡�\n");

	return 1;
}

nomask int is_array_skill() { return 1; }

void set_effective_level(int n)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(intp(n) && (n >= 10))
		e_level = n;
}

nomask int query_effective_level() { return e_level; }

nomask string query_menpai() { return mp; }

nomask void set_menpai(string arg)
{
	if(origin() != ORIGIN_LOCAL)
		return;
        
        if (! arg) return;
                mp = arg;
}

nomask int query_member_num() { return num; }

nomask void set_member_num(int n)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(intp(n) && (n > 0))
		num = n;
}

nomask  string query_name() { return name; }

nomask void set_array_name(string arg)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(stringp(arg) && arg != "")
		name = arg;
}

nomask void set_master_level(int n)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(n >= 0)
		master_level = n;
}

nomask void set_member_level(int n)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(n >= 0)
		member_level = n;
}

int valid_build(object who)
{
	int n;

	if(!who)
		return 0;

	if( mp && (who->query("family/family_name") != mp) )
	{
		tell_object(who,sprintf("ֻ�б����ɵ��Ӳ���ʹ�á�%s����\n",
			name ));
		return 0;
	}

	if(who->query_skill(ski_name,1) < master_level)
	{
		tell_object(who,sprintf("��ԡ�%s������ⲻ�����޷����ִ��󷨡�\n",
			name ));
		return 0;
	}

	if( !(n = who->query_skill(skill_type,1))
	|| (n < master_skill_level) )
	{
		tell_object(who,sprintf("��ġ�%s���ȼ�̫�ͣ��޷����֡�%s����\n",
			to_chinese(skill_type),name));
		return 0;
	}

	return 1;
}

int valid_member(object who)
{
	int n;

	if(!who)
		return 0;

	if(mp && (who->query("family/family_name") != mp) )
		return notify_fail(sprintf("ֻ�б����ɵ��Ӳ���ʹ�á�%s����\n",
			name ));

	if(who->query_skill(ski_name,1) < member_level)
		return notify_fail(sprintf("%s�ԡ�%s������ⲻ�����޷��μ�%s��\n",
			who->name(),name,name));

	if( !(n = who->query_skill(skill_type,1))
	|| (n < member_skill_level) )
		return notify_fail(sprintf("%s�ġ�%s���ȼ�̫�ͣ��޷��μӡ�%s����\n",
			who->name(),to_chinese(skill_type),name));

	return 1;
}

string success_msg()
{
	if(su_msg)
		return su_msg;

	else
		return sprintf(MAG BWHT"\n$N����ġ�%s����ʼ����������\n"NOR,name);
}

void set_success_msg(string arg)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(!stringp(arg) || sizeof(arg) < 3)
		return;

	if(arg[0] != '\n')
		arg = "\n" + arg;
	if(arg[<1] != '\n')
		arg += "\n";

	su_msg = arg;
}

void set_skill_type(string arg)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if( stringp(arg)
	|| (file_size(SKILL_D(arg)+".c") > 0) )
		skill_type = arg;
}

string query_array_skill()
{
	return skill_type;
}

void set_master_skill_level(int n)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(intp(n) && n > 0)
		master_skill_level = n;
}

int query_master_skill_level() { return master_skill_level; }

void set_member_skill_level(int n)
{
	if(origin() != ORIGIN_LOCAL)
		return;

	if(intp(n) && n > 0)
		member_skill_level = n;
}

int query_member_skill_level() { return member_skill_level; }
