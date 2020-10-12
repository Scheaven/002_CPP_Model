
double feature_distance(FEATURE feat1, FEATURE feat2)
{

    //将float格式的特征转化为tensor格式的特征
 
   double FeatA=0.0, FeatB=0.0, score=0.0;

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
 
   printf("--评分---%f--",score);
    return score;
}
