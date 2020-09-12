
double feature_distance(FEATURE feat1, FEATURE feat2)
{

    //��float��ʽ������ת��Ϊtensor��ʽ������
 
   double FeatA, FeatB, score;

   for (int i = 0; i < 128; i++)

    {
   
        FeatA += double(feat1[i])*double(feat1[i]);

        FeatB += double(feat2[i])*double(feat2[i]);

        score += double(feat1[i])*double(feat2[i]);

    }



    
    FeatA = sqrt(FeatA);
    
   FeatB = sqrt(FeatB);


   score = score / (FeatA * FeatB);
   if (score < 0) {
        score = 0;
    }
 
   printf("--����---%f--",score);
    return score;
}
