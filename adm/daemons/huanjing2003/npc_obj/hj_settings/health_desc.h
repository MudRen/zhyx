// health_desc.h  ��������   Ϊ��ͳһ qxd �� npc �����������
// naihe 05-9-1 11:35

string get_health_desc( int hp, int hp_max )
{
    if( hp >= hp_max )
        return HIG"�����������úܡ�"NOR;
    if( hp >= (hp_max *9/10) )
        return HIG"�ƺ����˵�����ˣ���������Ӱ�졣"NOR;
    if( hp >= (hp_max *8/10) )
        return HIG"���˵�����ˣ�������������ûʲô�󰭡�"NOR;
    if( hp >= (hp_max *6/10) )
        return HIY"��Ϣ��ʼ���ң������ƺ����˵�����ˡ�"NOR;
    if( hp >= (hp_max *5/10) )
        return HIY"��ڴ�ڵش��Ŵ������������β�̫���ˡ�"NOR;
    if( hp >= (hp_max *4/10) )
        return HIR"�������أ��Ų����ң�����ɢ����������Ҫ�ú���Ϣһ���ˡ�"NOR;
    if( hp >= (hp_max *2/10) )
        return RED"�Ѿ����˹��أ�һ����ʱ��Ҫ���µ����ӡ�"NOR;
    if( hp >= (hp_max *1/10) )
        return RED"�Ѿ��������أ�ֻʣ�����һ����Ϣ�ڿ��άϵ�š�"NOR;
    return RED"�Ѿ�ʧȥ����ʶ��������Ҫ�����ˡ�"NOR;
}
