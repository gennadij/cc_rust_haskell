module ExactRoot
(
  getExactSqrt,
  Res( .. )
) where
  
import Data.List ( partition )

data Res = Res {
  multiplicator :: Int,
  sqrt :: Int
} deriving (Eq, Show)

getExactSqrt :: Int -> [Res]
getExactSqrt inputRadikand = do
  if (inputRadikand < 0)
    then [Res (-1) (-1)]
    else 
      if inputRadikand == 0 || inputRadikand == 1
        then [Res (-1) inputRadikand]
        else calcPositiveSqrt inputRadikand

calcPositiveSqrt :: Int -> [Res]
calcPositiveSqrt positiveRadicand = do
  let radicandAndSqrt      = getRadicandAndSqrt positiveRadicand
  let simpleSqrt           = searchSimpleSqrt positiveRadicand radicandAndSqrt
  let complexSqrt          = searchComplexSqrt positiveRadicand radicandAndSqrt
  case simpleSqrt of 
    Just w -> [Res (-1) w]
    Nothing -> map (\(r,w) -> Res r w) complexSqrt

getRadicandAndSqrt :: Int -> [(Int, Int)] 
getRadicandAndSqrt rForRadicandAndSqrt = zip numsUpToRadicandHalf ((calcReducedDefaultSqrts rForRadicandAndSqrt))
  where 
    numsUpToRadicandHalf = [2 .. ((rForRadicandAndSqrt `quot` 2) + 1)]

calcReducedDefaultSqrts :: Int -> [Int]
calcReducedDefaultSqrts rForDdefault  = 
  case partition (< rForDdefault) (calcDefaultSqrts ( createOddNumbers rForDdefault )) of
    (xs, y:_) -> xs ++ [y]
    (xs, [])  -> xs
  where
    createOddNumbers :: Int -> [Int]
    createOddNumbers a = filter odd [1 .. a]
    calcDefaultSqrts :: [Int] -> [Int]
    calcDefaultSqrts  [] = []
    calcDefaultSqrts  [_] = []
    calcDefaultSqrts  (x:y:xs) = sumOfDefaultValues : calcDefaultSqrts (sumOfDefaultValues : xs)
      where sumOfDefaultValues = x + y

searchSimpleSqrt :: Int -> [(Int, Int)] -> Maybe Int
searchSimpleSqrt rForSimple radicandAndSqrt = unpuck (filter (\(_, b) -> b == rForSimple) radicandAndSqrt)
  where
    unpuck :: [(Int, Int)] -> Maybe Int
    unpuck [(a,_)] = Just a
    unpuck ((_,_):_) = Nothing
    unpuck []  = Nothing

searchComplexSqrt :: Int -> [(Int, Int)] -> [(Int, Int)]
searchComplexSqrt rForComplex radicandAndSqrt = unpuck (filter(\(_, b) -> (rForComplex `mod` b) == 0) radicandAndSqrt)
  where
    unpuck :: [(Int, Int)] -> [(Int, Int)]
    unpuck [] = []
    unpuck [(a, b)] = [(a, rForComplex `quot` b)]
    unpuck ((a, b) : c) = (a, rForComplex `quot` b): unpuck c
    