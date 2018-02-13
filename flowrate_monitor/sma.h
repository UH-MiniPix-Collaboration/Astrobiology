class SMAFilter{
  private:
    // Number of sample_fns to take
    int num_samples;
    int sample_delay;
    long int iter;
    // Array to store sample_fns in
    float* samples;
    // Function that returns a floating point value to filter
    float (*sample_fn)(void);

  public:
    SMAFilter(int count,float (*sample_fn)(void));
    ~SMAFilter();
    void setSampleCount(int count);
    float getFilteredSample();
    
};

SMAFilter::SMAFilter(int count, float (*sample_fn)(void))
{
  iter = 0;
  num_samples = count;
  this->sample_fn = sample_fn;
  samples = (float*)malloc(sizeof(float) * count);
}

void SMAFilter::setSampleCount(int count)
{
  num_samples = count;
  samples = (float*)realloc(samples, count);
}

float SMAFilter::getFilteredSample()
{
  float sample = this->sample_fn();
  float filtered_sample;
  float sum = 0;
  
  if(iter < num_samples){
    samples[iter] = sample;
    filtered_sample = sample;
  }else{
    sum=0;
    // Calculate moving average
    for(int i=0;i<num_samples;i++){
      sum += samples[i];
      filtered_sample = sum/num_samples;
    }
    // Shift values left
    for(int i=1;i<num_samples;i++){
      samples[i-1] = samples[i];
    }
    samples[num_samples-1] = sample;
  }
  this->iter++;
  return filtered_sample;
}


SMAFilter::~SMAFilter()
{
  free(samples);
}

