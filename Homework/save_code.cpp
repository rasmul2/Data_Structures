  int w = input.Width();
  int h = input.Height();
  input.SetAllPixels(5000);
  cout << "here" << endl;
  // return the maximum distance value
  double answer = 0;
  vector<DistancePixel> v;
   for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      const Color& c = input.GetPixel(i,j);     
      // skip all pixels that are not black
      if (c.isBlack()){
        cout << "hi" << endl;
        cout << "here" << endl;
        DistancePixel d = distance_image.GetPixel(i,j);
        d.setX(i);
        d.setY(j);
        d.setValue(0);
        cout << d.getX(); 
        input.SetPixel(i,j,0);
        v.push_back(d);
      } 
    }
  }
  cout << v.size();

  DistancePixel_PriorityQueue pg;
  double closest = -1;
   for (vector<DistancePixel>::iterator i = v.begin(); i != v.end(); ++i)
   {
      cout << "here" << endl;
     for (int j = i->getX()-1; j < i->getY()+2; ++j)
     {
       for (int k = i->getX()-1; k < i->getY() +2; ++k)
       {
         if (j== i->getX() && k== i->getY()) continue;
         double distance = sqrt((j-i->getX())*(j-i->getX()) + (k-i->getY())*(k-i->getY()));
          // store the closest distance to a black pixel
          if (closest < 0 || distance < closest) {
            closest = distance;
          }
          assert (closest >= 0);
          answer = std::max(answer,closest);
          // save the data to the distance image
           DistancePixel& d = distance_image.GetPixel(j,k);
           d.setValue(closest);
           DistancePixel* p = &d;
           cout << "here" << endl;
            cout << d;  
           pg.push(p);
        }
     }
   }

   cout << pg.size(); 