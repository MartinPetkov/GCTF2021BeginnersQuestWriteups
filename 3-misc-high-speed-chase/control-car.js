/* The controlCar function will be called several times per second during the chase to allow for course corrections.

The controlCar function takes a single parameter – scanArray – which is an array containing 17 integers denoting distance from your car to the nearest obstacle:

[indexes 0-7]: on the left side of the car (index 7 is the measurement at the left headlight),
[index 8]: at the center of the car,
[indexes 9-16]: on the right side of the car (index 9 is the measurement at the right headlight).

All measurements are parallel to each other.

A negative measurement might appear if the obstacle is very close behind our car.

The controlCar must return an integer denoting where the car should drive:

-1 (or any other negative value): drive more to the left,
0: continue straight / straighten up the car,
1 (or any other positive value): drive more to the right.
*/

function controlCar(scanArray) {
  // Treat them as absolute values, since we only
  // care about distance, not forward-or-backwards.
  const scanArrayAbs = scanArray.map(e => Math.abs(e));
  console.log(scanArray);
  console.log(scanArrayAbs);
  console.log(`Center lane: ${scanArray.slice(7,10)}`);

  // We'll look for a best "lane", a group of 3 spots.

  // Determine the best lane on the left.
  const bestLeft = Math.max(...scanArrayAbs.slice(0, 7));
  console.log(`bestLeft is ${bestLeft}`);

  // Determine the best if we stay going straight.
  const bestStraight = Math.min(scanArrayAbs[7], scanArrayAbs[8], scanArrayAbs[9]);
  console.log(`bestStraight is ${bestStraight}`);

  // Determine the best on the right.
  const bestRight = Math.max(...scanArrayAbs.slice(10));
  console.log(`bestRight is ${bestRight}`);

  // Decide where to go.
  if ((bestStraight >= bestLeft) && (bestStraight >= bestRight)) {
    console.log('Go straight!');
    return 0;
  }

  if ((bestLeft > bestStraight) && (bestLeft > bestRight)) {
      console.log('Go left!');
      return -1;
  }

  if ((bestRight > bestStraight) && (bestRight >= bestLeft)) {
      console.log('Go right!');
      return 1;
  }

  // Else, just go straight.
  console.log('Fallback go straight');
  return 0;
}

