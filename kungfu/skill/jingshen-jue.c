// jingshen-jue �����ڹ��ķ��������
// By Alf, Last Update 2001.10

inherit FORCE;

int valid_enable(string usage)
{
    return usage == "force";
}

int valid_learn(object me)
{
    int lvl = (int)me->query_skill("jingshen-jue", 1);

    if ((int)me->query_skill("force", 1) < 30)
        return notify_fail("��Ļ����ڹ����δ��������ѧϰ�������\n");

    if (
    me->query_skill("bahuang-gong",1)    // ���գ��˻����Ϲ�
    || me->query_skill("beiming-shengong",1)    // ��ң����ڤ��
    || me->query_skill("bibo-shengong",1)    // �һ����̲���
    || me->query_skill("chunyang-gong",1)    // ����������
    || me->query_skill("hamagong",1)    // ���գ���󡹦
    || me->query_skill("huagong-dafa",1)    // ���ޣ�������
    || me->query_skill("huntian-qigong",1)    // ؤ���������
    || me->query_skill("hunyuan-yiqi",1)    // ���֣���Ԫһ����
    || me->query_skill("jiuyang-shengong",1)    // ���֣�������
    || me->query_skill("linji-zhuang",1)    // ���ң��ټ�ʮ��ׯ
    || me->query_skill("longhu-baqi",1)    // ��٣���������
    || me->query_skill("nilian-shengong",1)    // ���գ�������
    || me->query_skill("shenlong-zhanqi",1)    // ����������ս��
    || me->query_skill("taiji-shengong",1)    // �䵱��̫����
    || me->query_skill("wolong-xingfa",1)    // Ѳ���������ķ�
    || me->query_skill("wuwang-shenzhou",1)    // �����ǣ���������
    || me->query_skill("xiantian-gong",1)    // ȫ�棺���칦
    || me->query_skill("xiawuxiang",1)    // ѩɽ��С���๦
    || me->query_skill("xuanmen-neigong",1)    // ȫ�棺�����ڹ�
    || me->query_skill("yunlong-shengong",1) // ������������
    || me->query_skill("zixia-shengong",1) )    // ��ɽ����ϼ��
        return notify_fail("�㲻��ɢ�˱����ڹ�������ѧ���������\n");
    return 1;
}


int practice_skill(object me)
{
    return notify_fail("�����ֻ��ͨ��ѧϰ(xue)�����Ǵ�����(yun)�����������ȡ�\n");
}

string exert_function_file(string func)
{
    return "/kungfu/skill/jingshen-jue/" + func;
    }

